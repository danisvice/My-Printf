#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

void my_printf(char* format, va_list args);
char* convert(unsigned int, int);

int main(int argc, char* argv[])
{
    my_printf(argv[1], NULL);
    return 0;
}

void my_printf(char* format, va_list args)
{
    unsigned int i;
    char* input;
    char* s;
    void* p;
    
    for(input = format; *input != '\0'; input++)
    {
        while(*input != '%')
        {
                putchar(*input);
                input++;
        }
        input++;
        
            //FETCH & EXECUTE VARIABLE CONVERSION
        switch(*input)
        {
                case 'd' : i = va_arg(args, int);
                                if(i<=0)
                                {
                                    i = -i;
                                    write(1, "-", 1);
                                }
                                write(1, convert(i, 10), strlen(convert(i, 10)));
                                break;
                
                case 'o' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 8),  strlen(convert(i, 8)));
                                break;
             

                case 'u' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 10), strlen(convert(i, 10)));
                                break;
                

                case 'x' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 16), strlen(convert(i, 16)));
                                break;
                

                case 'c' : i = va_arg(args, int);
                                write(1, &i, 1);
                                break;


                case 's' : s = va_arg(args, char*);
                                write(1, s, strlen(s));
                                break;
                

                case 'p' : p = va_arg(args, void*);
                                intptr_t ptr_val = (intptr_t)p;
                                write(1, convert(ptr_val, 16), strlen(convert(ptr_val, 16)));
                                break;
        }
    }
    va_end(args);
    //return 0;
}

char* convert(unsigned int n, int base)
{
            static char Rep[] = "0123456789ABCDEF";
            static char buffer[50];
            char *ptr;

            ptr = &buffer[49];
            *ptr = '\0';

            do
            {
                *--ptr = Rep[n%base];
                n /= base;
            }
            while(n!=0);
        
            return(ptr);
}