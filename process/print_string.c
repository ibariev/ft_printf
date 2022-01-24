#include "../ft_printf.h"

static void	print_string_minus(t_flags *flags, int *len, char *s)
{
	int	i;

	if (flags->dot)
	{
		i = -1;
		while (++i < flags->precision && i < (int) ft_strlen(s))
			ft_putchar_fd(s[i], 1);
		while (i < flags->width)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		(*len) += i;
	}
	else
	{
		ft_putstr_fd(s, 1);
		i = ft_strlen(s);
		while (i < flags->width)
		{
			ft_putchar_fd(' ', 1);
			i++;
		}
		(*len) += i;
	}
}

static void	print_string_no_minus(t_flags *flags, int *len, char *s)
{
	int	i;
	int	j;
	int	size;

	size = (int) ft_strlen(s);
	if (flags->dot)
	{
		i = -1;
		while (++i < flags->width - flags->precision || i < flags->width - size)
			ft_putchar_fd(' ', 1);
		j = -1;
		while (++j < flags->precision && j < size)
			ft_putchar_fd(s[j], 1);
		(*len) += i + j;
	}
	else
	{
		i = -1;
		while (++i < flags->width - size)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(s, 1);
		(*len) += i + size;
	}
}

void	print_string(va_list args, t_flags *flags, int *len)
{
	char	*s;

	s = va_arg(args, char *);
	if (s == NULL)
		s = "(null)";
	if (flags->precision < 0)
		flags->precision += INT_MAX;
	if (flags->minus)
		print_string_minus(flags, len, s);
	else
		print_string_no_minus(flags, len, s);
}
