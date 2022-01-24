#include "../ft_printf.h"

static void	convert_pointer(char *a, unsigned long nbr, int *i, t_flags *flags)
{
	if (nbr == 0 && flags->dot && flags->precision == 0)
		return ;
	if (nbr % 16 < 10)
		a[*i] = (nbr % 16 + 48);
	else
		a[*i] = (nbr % 16 + 87);
	(*i)++;
}

static void	create_array(char *address, unsigned long nbr, t_flags *flags)
{
	int		i;
	int		size;
	char	temp;

	i = 0;
	while (nbr >= 16)
	{
		convert_pointer(address, nbr, &i, flags);
		nbr /= 16;
	}
	convert_pointer(address, nbr, &i, flags);
	address[i] = 'x';
	address[i + 1] = '0';
	address[i + 2] = '\0';
	size = (int) ft_strlen(address);
	i = -1;
	while (++i < size / 2)
	{
		temp = address[size - 1 - i];
		address[size - 1 - i] = address[i];
		address[i] = temp;
	}
}

void	print_pointer(va_list args, t_flags *flags, int *len)
{
	unsigned long		nbr;
	char				address[17];
	int					i;
	int					j;

	nbr = (unsigned long) va_arg(args, void *);
	create_array(address, nbr, flags);
	i = -1;
	if (flags->minus)
	{
		while (++i < (int) ft_strlen(address))
			ft_putchar_fd(address[i], 1);
		while (i++ < flags->width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (++i < flags->width - (int) ft_strlen(address))
			ft_putchar_fd(' ', 1);
		j = i + 1;
		while (++i - j < (int) ft_strlen(address))
			ft_putchar_fd(address[i - j], 1);
	}
	(*len) += i - 1;
}
