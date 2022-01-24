#include "ft_printf.h"

int	ft_process(int len, va_list args, t_flags *flags)
{
	if (flags->spec == 'c')
		print_char(args, flags, &len);
	else if (flags->spec == 's')
		print_string(args, flags, &len);
	else if (flags->spec == 'p')
		print_pointer(args, flags, &len);
	else if (flags->spec == 'd' || flags->spec == 'i')
		print_integer(args, flags, &len);
	else if (flags->spec == 'u')
		print_unsigned(args, flags, &len);
	else if (flags->spec == 'x' || flags->spec == 'X')
		print_hexadecimal(args, flags, &len);
	else if (flags->spec == '%')
		print_percent(flags, &len);
	return (len);
}
