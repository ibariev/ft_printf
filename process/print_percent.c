#include "../ft_printf.h"

void	print_percent(t_flags *flags, int *len)
{
	int	i;

	i = -1;
	if (flags->minus)
	{
		ft_putchar_fd('%', 1);
		while (++i < flags->width - 1)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		if (flags->zero)
			while (++i < flags->width - 1)
				ft_putchar_fd('0', 1);
		else
			while (++i < flags->width - 1)
				ft_putchar_fd(' ', 1);
		ft_putchar_fd('%', 1);
	}
	(*len) += i + 1;
}
