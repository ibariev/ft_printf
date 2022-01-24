#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int				minus;
	int				zero;
	int				width;
	int				dot;
	int				spec;
	int				precision;
}					t_flags;

int		ft_printf(const char *s, ...);
int		ft_analyze(va_list args, const char *s);
int		ft_analyze_flags(int i, va_list args, const char *s, t_flags *flags);
int		ft_process(int i, va_list args, t_flags *flags);
void	print_char(va_list args, t_flags *flags, int *len);
void	print_string(va_list args, t_flags *flags, int *len);
void	print_pointer(va_list args, t_flags *flags, int *len);
void	print_integer(va_list args, t_flags *flags, int *len);
void	print_unsigned(va_list args, t_flags *flags, int *len);
void	print_hexadecimal(va_list args, t_flags *flags, int *len);
void	print_percent(t_flags *flags, int *len);

#endif