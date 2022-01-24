#include "../ft_printf.h"

static int	count_digits(int *nbr, int *sign, t_flags *flags)
{
	int	digits;
	int	num;

	if (flags->precision == 0 && flags->dot && *nbr == 0)
		return (0);
	digits = 1;
	num = *nbr;
	while (num >= 10 || num <= -10)
	{
		digits++;
		num /= 10;
	}
	if (*nbr < 0)
	{
		*sign = 1;
		(*nbr) *= -1;
	}
	return (digits);
}

static void	print_integer_no_zero(t_flags *flags, int *i, int digits, int sign)
{
	int	wid;
	int	prec;

	wid = flags->width;
	prec = flags->precision;
	while (++(*i) < wid - prec - sign && *i < wid - digits - sign)
		ft_putchar_fd(' ', 1);
	if (sign)
		ft_putchar_fd('-', 1);
	prec += *i;
	while ((*i)++ < prec - digits)
		ft_putchar_fd('0', 1);
}

static void	print_integer_no_minus(t_flags *flags, int *len, int nbr)
{
	int	i;
	int	sign;
	int	digits;

	sign = 0;
	digits = count_digits(&nbr, &sign, flags);
	i = -1;
	if (flags->zero)
	{	
		if (sign)
			ft_putchar_fd('-', 1);
		while (++i < flags->width - digits - sign)
			ft_putchar_fd('0', 1);
		i++;
	}
	else
		print_integer_no_zero(flags, &i, digits, sign);
	if (nbr == INT_MIN)
		ft_putstr_fd("2147483648", 1);
	else if (flags->precision == 0 && flags->dot && nbr == 0)
		;
	else
		ft_putnbr_fd(nbr, 1);
	i += digits + sign;
	(*len) += i - 1;
}

static void	print_integer_minus(t_flags *flags, int *len, int nbr)
{
	int	i;
	int	sign;
	int	digits;

	sign = 0;
	digits = count_digits(&nbr, &sign, flags);
	if (sign)
		ft_putchar_fd('-', 1);
	i = -1;
	while (++i < flags->precision - digits)
		ft_putchar_fd('0', 1);
	if (nbr == INT_MIN)
		ft_putstr_fd("2147483648", 1);
	else if (flags->precision == 0 && flags->dot && nbr == 0)
		;
	else
		ft_putnbr_fd(nbr, 1);
	i += digits + sign;
	while (i++ < flags->width)
		ft_putchar_fd(' ', 1);
	(*len) += i - 1;
}

void	print_integer(va_list args, t_flags *flags, int *len)
{
	int	nbr;

	nbr = va_arg(args, int);
	if (flags->minus)
		print_integer_minus(flags, len, nbr);
	else
		print_integer_no_minus(flags, len, nbr);
}
