#include "ft_printf.h"

static void	handle_zero_minus(t_flags *flags, int *i, const char *s)
{
	if (s[*i] == '0')
		flags->zero = 1;
	else
	{
		flags->minus = 1;
		flags->zero = 0;
	}
	(*i)++;
}

static void	handle_width(t_flags *flags, int *i, va_list args, const char *s)
{
	int	width;

	if (s[*i] == '*')
	{
		flags->width = va_arg(args, int);
		if (flags->width < 0)
		{
			flags->minus = 1;
			flags->zero = 0;
			flags->width *= -1;
		}
		(*i)++;
		return ;
	}
	width = 0;
	while (ft_isdigit(s[*i]))
	{
		width = width * 10 + (int)(s[*i] - 48);
		(*i)++;
	}
	flags->width = width;
}

static void	handle_dot(t_flags *flags, int *i, va_list args, const char *s)
{
	int	prec;

	flags->dot = 1;
	(*i)++;
	if (s[*i] == '*')
	{
		flags->precision = va_arg(args, int);
		(*i)++;
		return ;
	}
	prec = 0;
	while (ft_isdigit(s[*i]))
	{
		prec = prec * 10 + (int)(s[*i] - 48);
		(*i)++;
	}
	flags->precision = prec;
}

static void	handle_spec(t_flags *flags, int *i, const char *s)
{
	flags->spec = s[*i];
	if (flags->dot && flags->spec != '%' && flags->precision >= 0)
		flags->zero = 0;
}

int	ft_analyze_flags(int i, va_list args, const char *s, t_flags *flags)
{
	i++;
	if (s[i] == ' ')
		i++;
	if ((ft_strchr("-0.*cspdiuxX%", s[i]) && s[i] != '\0') || ft_isdigit(s[i]))
	{
		while (s[i] == '0' || s[i] == '-')
			handle_zero_minus(flags, &i, s);
		if (s[i] == '*' || ft_isdigit(s[i]))
			handle_width(flags, &i, args, s);
		if (s[i] == '.')
			handle_dot(flags, &i, args, s);
		if (ft_strchr("cspdiuxX%", s[i]) && s[i] != '\0')
			handle_spec(flags, &i, s);
	}
	return (i);
}
