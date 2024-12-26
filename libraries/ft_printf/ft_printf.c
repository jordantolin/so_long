/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtolin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:33:48 by jtolin            #+#    #+#             */
/*   Updated: 2024/01/16 18:33:50 by jtolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format(char specifier, va_list ap)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len += ft_putchar(va_arg(ap, int));
	else if (specifier == 's')
		len += ft_putstr(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		len += ft_putnbr(va_arg(ap, int));
	else if (specifier == 'u')
		len += ft_putunbr(va_arg(ap, unsigned int));
	else if (specifier == 'x')
		len += ft_puthex(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (specifier == 'X')
		len += ft_puthex(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (specifier == 'p')
		len += ft_putptr(va_arg(ap, unsigned long long));
	else
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;
	int		i;

	len = 0;
	i = -1;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_print_format(format[i], ap);
		}
		else
			len += ft_putchar(format[i]);
	}
	va_end(ap);
	return (len);
}
