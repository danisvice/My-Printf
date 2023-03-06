#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int convert(char *dest, unsigned long long n, int base, const char *digits) {
    char buffer[sizeof(n) * CHAR_BIT];
    char *ptr = buffer;
    int len = 0;

    do {
        *ptr++ = digits[n % base];
        n /= base;
    } while (n != 0);

    while (ptr > buffer) {
        dest[len++] = *--ptr;
    }
    dest[len] = '\0';
    return len;
}

int my_printf(const char *format, ...) {
    static const char rep_lower[] = "0123456789abcdef";
    static const char rep_upper[] = "0123456789ABCDEF";
    unsigned long long n;
    char buffer[sizeof(n) * CHAR_BIT + 3];
    va_list args;
    int i, len;
    const char *input, *last;
    const char *s;
    char *r;
    void *p;
    int res = 0;

    va_start(args, format);
    for (input = last = format;; input++) {
        /* scan for a conversion specification */
        if (*input != '\0' && (*input != '%' || input[1] == '\0'))
            continue;
        if (input > last) {
            /* output pending format string fragment */
            res += write(1, last, input - last);
        }
        if (*input == '\0')
            break;
        input++;
        last = input + 1;
        //FETCH & EXECUTE VARIABLE CONVERSION
        s = r = buffer;
        switch (*input) {
            case '%': *r = '%';
                        len = 1;
                        break;

        case 'd':  n = i = va_arg(args, int);
                        if (i < 0) 
                        {
                            *r++ = '-';
                            n = -n;
                        }
                        len = convert(r, n, 10, rep_lower) + (r - s);
                        break;

        case 'u':  n = va_arg(args, unsigned int);
                        len = convert(r, n, 10, rep_lower);
                        break;

        case 'b': n = va_arg(args, unsigned int);
                        len = convert(r, n, 2, rep_lower);
                        break;

        case 'o': n = va_arg(args, unsigned int);
                        len = convert(r, n, 8, rep_lower);
                        break;

        case 'x': n = va_arg(args, unsigned int);
                        len = convert(r, n, 16, rep_upper);
                        break;

        case 'X': n = va_arg(args, unsigned int);
                        len = convert(r, n, 16, rep_upper);
                        break;

        case 'c': *r = (char)va_arg(args, int);
                        len = 1;
                        break;

        case 's': s = va_arg(args, char *);
                    if (s == NULL) 
                    {
                        s = "(null)";
                    }
                        len = strlen(s);
                        break;

        case 'p': p = va_arg(args, void *);
                        n = (unsigned long long)(intptr_t)p;
                        *r++ = '0';
                        *r++ = 'x';
                        len = convert(r, n, 16, rep_lower) + (r - s);
                        break;

        default: s = input - 1;
                        len = 2;
                        break;
        }
        res += write(1, s, len);
    }
    va_end(args);
    return res;
}
