#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int my_printf(char * restrict format, ...)
{
    char* str;
    va_list args;
    va_start(format, args);

    for(int i = 0; i < format; i++)
    {
        write(1, str, 100)
        {
            switch(str)
            {
                case 'd' :
                va_arg()
                break;

                case 'o' :
                return int str;
                break;

                case 'u' :
                return int str;
                break;

                case 'x' :
                return int str;
                break;

                case 'c' :
                return int str;
                break;

                case 's' :
                return int str;
                break;

                case 'p' :
                return int str;
                break;
            }
        };
    }
}