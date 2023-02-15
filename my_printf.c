#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int my_printf(char * restrict format, ...)
{
    char* str;

    for(int i = 0; i < format; i++)
    {
        write(1, str, 100)
        {
            switch(str)
            {
                case %d:
                return int str;
                break;
            }
        };
    }
}