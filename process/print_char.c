#include "../ft_printf.h"

void	print_char(va_list args, t_flags *flags, int *len)
{
	int	i;

	i = -1;
	if (flags->minus)
	{
		ft_putchar_fd(va_arg(args, int), 1);
		while (++i < flags->width - 1)
		{
			ft_putchar_fd(' ', 1);
			(*len)++;
		}
	}
	else
	{
		while (++i < flags->width - 1)
		{
			ft_putchar_fd(' ', 1);
			(*len)++;
		}
		ft_putchar_fd(va_arg(args, int), 1);
	}
	(*len)++;
}
