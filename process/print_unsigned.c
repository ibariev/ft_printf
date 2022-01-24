#include "../ft_printf.h"

static int	count_unsigned_digits(unsigned int nbr, t_flags *flags)
{
	int	digits;

	if (flags->precision == 0 && flags->dot && nbr == 0)
		return (0);
	digits = 1;
	while (nbr >= (unsigned int) 10)
	{
		digits++;
		nbr /= 10;
	}
	return (digits);
}

static void	ft_put_unsigned(unsigned int n)
{
	char	ch;

	if (n > 9)
		ft_put_unsigned(n / 10);
	ch = (char)(n % 10 + 48);
	write(1, &ch, 1);
}

static void	print_unsigned_no_minus(t_flags *flags, int *len, int nbr)
{
	int	i;
	int	dig;
	int	prec;

	dig = count_unsigned_digits(nbr, flags);
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
		prec = flags->precision + i;
		while (i++ < prec - dig)
			ft_putchar_fd('0', 1);
	}
	if (flags->precision == 0 && flags->dot && nbr == 0)
		;
	else
		ft_put_unsigned(nbr);
	(*len) += i + dig - 1;
}

static void	print_unsigned_minus(t_flags *flags, int *len, int nbr)
{
	int	i;
	int	digits;

	digits = count_unsigned_digits(nbr, flags);
	i = -1;
	while (++i < flags->precision - digits)
		ft_putchar_fd('0', 1);
	if (flags->precision == 0 && flags->dot && nbr == 0)
		;
	else
		ft_put_unsigned(nbr);
	i += digits;
	while (i++ < flags->width)
		ft_putchar_fd(' ', 1);
	(*len) += i - 1;
}

void	print_unsigned(va_list args, t_flags *flags, int *len)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	if (flags->minus)
		print_unsigned_minus(flags, len, nbr);
	else
		print_unsigned_no_minus(flags, len, nbr);
}
