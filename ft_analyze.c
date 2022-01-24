#include "ft_printf.h"

static void	init_struct(t_flags *flags)
{
	flags->minus = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->dot = 0;
	flags->spec = 0;
	flags->precision = 0;
}

static void	ft_putchar(char	ch, int *len)
{
	write(1, &ch, 1);
	(*len)++;
}

int	ft_analyze(va_list args, const char *s)
{
	int		i;
	int		len;
	t_flags	flags;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			init_struct(&flags);
			if (s[i + 1] == ' ')
				ft_putchar(' ', &len);
			i = ft_analyze_flags(i, args, s, &flags);
			if (flags.spec != 0)
				len = ft_process(len, args, &flags);
			else
				ft_putchar(s[i], &len);
		}
		else
			ft_putchar(s[i], &len);
		if (s[i] != '\0')
			i++;
	}
	return (len);
}
