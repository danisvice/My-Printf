#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

//void mprintf(char* format, ...);
char* convert(unsigned int, int);

int my_printf(char* format, ...)
{
    va_list args;
    va_start(args, format);
    int d;
    unsigned int i;
    char* input;
    char* s;
    void* p;
    int sum = 0;
    
    for(input = format; *input != '\0'; input++)
    {
        if(*input == '%'){
        input++;
        //FETCH & EXECUTE VARIABLE CONVERSION
        switch(*input)
        {
                case '%' :      write(1, "%", 1);
                                sum++;
                                break;

                case 'd' : d = va_arg(args, int);
                                
                                if(d < 0)
                                {
                                    d = -d;
                                    sum++;
                                } 
                                else 
                                
                                write(1, convert(d, 10), strlen(convert(d, 10)));
                                sum += strlen(convert(d, 10));
                                break;       
                
                case 'o' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 8),  strlen(convert(i, 8)));
                                sum += strlen(convert(i, 8));
                                break;
             
                case 'u' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 10), strlen(convert(i, 10)));
                                sum += strlen(convert(i, 10));
                                break;
                
                case 'x' : i = va_arg(args, unsigned int);
                                write(1, convert(i, 16), strlen(convert(i, 16)));
                                sum += strlen(convert(i,16));
                                break;
                
                case 'c' : i = va_arg(args, int);
                                write(1, &i, 1);
                                sum++;
                                break;

                case 's' : s = va_arg(args, char*);

                                if(s == NULL)
                                {
                                    write(1,"NULL STRING (null)!",0);
                                    sum += 0;
                                }
                                else 
                                
                                write(1, s, strlen(s));
                                sum += strlen(s);
                                break;

                case 'p' : p = va_arg(args, void*);
                                intptr_t ptr_val = (intptr_t)p;
                                write(1, convert(ptr_val, 16), strlen(convert(ptr_val, 16)));
                                sum += strlen(convert(ptr_val, 16));
                                break;

                default: 
                                write(1, input-1, 2);
                                sum += 2;
                                break;
        }
        }
        else 
            {
                write(1, input, 1);
                sum++;
            }            
        
    }
    va_end(args);
    return sum;
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