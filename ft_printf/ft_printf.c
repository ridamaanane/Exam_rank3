#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int count  = 0;

void ft_putchar(char c)
{
    count++;
    write(1, &c, 1);
}

void puthexa_l(unsigned int n)
{
    char *base;
    base = "0123456789abcdef";
    if (n >= 16)
        puthexa_l(n / 16);
    ft_putchar(base[n % 16]);
}
void ft_putstr(char *str)
{
    if (!str)
        count += write(1, "(null)", 6);
    while (str && *str)
        ft_putchar(*str++);
}

void ft_putnbr(int n)
{
    unsigned int nb;
    if (n < 0)
    {
        ft_putchar('-');
        nb = -n;
    }
    else 
        nb = n;
    if (nb >= 10)
        ft_putnbr(nb / 10);
    ft_putchar(nb % 10 + 48);
}

void ft_check(va_list args,  char format)
{
    if (format == 's')
        ft_putstr(va_arg(args, char *));
    else if (format == 'd')
        ft_putnbr(va_arg(args, int));
    else if (format == 'x')
        puthexa_l(va_arg(args, unsigned int));
}

int ft_printf(const char *format, ... )
{
    int i = 0;
    va_list args;
    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%' && format[i + 1] != '\0')
        {
            ft_check(args, format[i + 1]);
            i++;
        }
        else
            ft_putchar(format[i]);
        i++;
    }
    va_end(args);
    i = count;
    count = 0;
    return (i);
}
