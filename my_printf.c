#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int my_printf(char * restrict format, ...)
{
    unsigned int i;
    char* input;
    char* s;
    char* convert(unsigned int, int);

    va_list args;
    va_start(args, format);
    
    for(input = format; *input != '\0'; input++)
    {
        while(*input != '%')
        {
            putchar(*input);
            input++;
        }
        
        input++;
        
        {
            //FETCH & EXECUTE VARIABLE CONVERSION
            switch(*input)
            {
                case 'd' :
                {
                    i = va_arg(args, int);
                    if(i<0)
                    {
                        i = -1;
                        putchar('-');
                    }
                    puts(convert(i,10));
                    break;
                }

                case 'o' :
                {
                    format[i] = va_arg(args, unsigned octal);
                }

                case 'u' :
                {
                    format[i] = va_arg(args, unsigned decimal);
                }

                case 'x' :
                {
                    format[i] = va_arg(args, unsigned hex);
                }

                case 'c' :
                {
                    i = va_arg(args, int);
                    putchar(i);
                    break;
                }

                case 's' :
                {
                    format[i] = va_arg(args, char*);
                }

                case 'p' :
                {
                    format[i] = va_arg(args, void*);
                }
            }
        }
    }
}
