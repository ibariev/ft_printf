#include "ft_printf.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, s);
	len = ft_analyze(args, s);
	va_end(args);
	return (len);
}
