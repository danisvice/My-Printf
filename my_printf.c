#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define BUF_SIZE 256;

int my_printf(char * restrict format, ...)
{
    char buf[256];
    va_list args;
    va_start(args, format);
    unsigned int i;
    int buf_i = 0;

    for(int i = 0; format[i] != '\0'; i++)
    {
        
        if(format[i] != '%')
        {
            write(1, &format[i], 1);
            buf[buf_i++] = format[i]; 
        } 
        else 
        {
            //VARIABLE CONVERSION
            switch(format[i])
            {
                case 'd' :
                {
                format[i] = va_arg(args, int);
                
                }

                case 'o' :
                {
                    format[i] = va_arg(args, unsigned octal);
                }

                case 'u' :
                {
                    format[i] = va_args(args, unsigned decimal);
                }

                case 'x' :
                {
                    format[i] = va_args(args, unsigned hex);
                }

                case 'c' :
                {
                    format[i] = va_args(args, char);
                }

                case 's' :
                {
                    format[i] = va_args(args, char*);
                }

                case 'p' :
                {
                    format[i] = va_args(args, void*);
                }
            }
        }
    }
}
