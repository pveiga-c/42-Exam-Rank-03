#include <unistd.h>
#include <stdarg.h>

void    ft_str(char *str, int *len)
{
    if(*str == NULL)
        *str = "(null)";
    while(*str)
    {
        write(1, *str, 1);
        *len++;
    }
}

void    hex_digit(long long int num, int base, int *len)
{
    if(num < 0)
    {
        num = num * -1;
        write(1, "-", 1);
        *len++;
    }
    if(num >= base)
        hex_digit((num / base), base, &len);
    write(1, &"0123456789abcdef"[num % base], 1);
    *len++;
}

int ft_print(const char *str, ...)
{
    int len;

    len = 0;
    va_list(pointer);
    va_start(pointer, str);
    while(*str)
    {
        if(*str == '%' && (*str + 1))
        {
            *str++;
            if(str == 's')
                ft_str(va_arg(pointer, char *), &len);
            if(str == 'd')
                hex_digit((long long int)(va_arg(pointer, int)), 10, &len);
            if(str == 'x')
                hex_digit((long long int)(va_arg(pointer, unsigned int)), 16, &len);
        }
        else
        {
            write(1, str, 1);
            len++;
        } 
    }
    va_end(pointer);
    return (len);
}
