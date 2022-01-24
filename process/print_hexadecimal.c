#include "../ft_printf.h"

static void	convert_nbr(char *array, unsigned int nbr, int *i, t_flags *flags)
{
	if (flags->precision == 0 && flags->dot && nbr == 0)
		return ;
	if (nbr % 16 < 10)
		array[*i] = (nbr % 16 + 48);
	else
	{
		if (flags->spec == 'x')
			array[*i] = (nbr % 16 + 87);
		else
			array[*i] = (nbr % 16 + 55);
	}
	(*i)++;
}

static void	create_array(char *array, unsigned int nbr, t_flags *flags)
{
	int		i;
	int		size;
	char	temp;

	i = 0;
	while (nbr >= 16)
	{
		convert_nbr(array, nbr, &i, flags);
		nbr /= 16;
	}
	convert_nbr(array, nbr, &i, flags);
	array[i] = '\0';
	size = (int) ft_strlen(array);
	i = -1;
	while (++i < size / 2)
	{
		temp = array[size - 1 - i];
		array[size - 1 - i] = array[i];
		array[i] = temp;
	}
}

static void	print_hex_minus(t_flags *flags, int *len, char *array)
{
	int	i;
	int	j;
	int	digits;

	digits = ft_strlen(array);
	i = -1;
	while (++i < flags->precision - digits)
		ft_putchar_fd('0', 1);
	j = -1;
	while (array[++j] != '\0')
		ft_putchar_fd(array[j], 1);
	i += digits;
	while (i++ < flags->width)
		ft_putchar_fd(' ', 1);
	(*len) += i - 1;
}

static void	print_hex_no_minus(t_flags *flags, int *len, char *array)
{
	int	i;
	int	j;
	int	dig;

	dig = ft_strlen(array);
	i = -1;
	if (flags->zero)
	{	
		while (++i < flags->width - dig)
			ft_putchar_fd('0', 1);
		i++;
	}
	else
	{
		while (++i < flags->width - flags->precision && i < flags->width - dig)
			ft_putchar_fd(' ', 1);
		flags->precision += i;
		while (i++ < flags->precision - dig)
			ft_putchar_fd('0', 1);
	}
	j = -1;
	while (array[++j] != '\0')
		ft_putchar_fd(array[j], 1);
	i += dig;
	(*len) += i - 1;
}

void	print_hexadecimal(va_list args, t_flags *flags, int *len)
{
	unsigned int	nbr;
	char			array[9];

	nbr = va_arg(args, unsigned int);
	create_array(array, nbr, flags);
	if (flags->minus)
		print_hex_minus(flags, len, array);
	else
		print_hex_no_minus(flags, len, array);
}
