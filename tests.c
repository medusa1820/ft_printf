#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

int	conversion_type(va_list args, const char frmt);
int	conversion(int *print_len, int *i, va_list args, const char frmt);
int	no_conversion(int *print_len, const char str);

int	ft_putchar(char c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (*(s + i) == (char)c)
		return (((char *)s + i));
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_nmbr_base_len(long int n, size_t base_len)
{
	size_t	i;

	i = 1;
	while (n >= (long int)base_len)
	{
		n = n / base_len;
		i++;
	}
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;
	int		print_len;

	print_len = 0;
	i = 0;
	va_start(args, s);
	while (s[i])
	{
		if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]) != 0)
		{
			if (conversion(&print_len, &i, args, s[i + 1]) == -1)
				return (-1);
		}
		else
		{
			if (no_conversion(&print_len, s[i]) == -1)
				return (-1);
		}
		i++;
	}
	va_end(args);
	return (print_len);
}

int	ft_put_nmbr(long int n)
{
	const char	*base = "0123456789";
	int			a;
	int			nmbr_len;

	nmbr_len = 0;
	if (n < 0)
	{
		if (write(1, "-", 1) != 1)
			return (-1);
		a = ft_put_nmbr(-n);
		if (a == -1)
			return (-1);
		nmbr_len += a;
	}
	else if (n >= 10)
	{
		if ((ft_put_nmbr(n / 10) == -1) || \
			ft_put_nmbr(n % 10) == -1)
			return (-1);
	}
	else
		if (write (1, &base[n], 1) != 1)
			return (-1);
	nmbr_len += ft_nmbr_base_len(n, ft_strlen(base));
	return (nmbr_len);
}

int	conversion(int *print_len, int *i, va_list args, const char frmt)
{
	int		nr_of_chars;

	nr_of_chars = conversion_type(args, frmt);
	if (nr_of_chars == -1)
		return (-1);
	*print_len += nr_of_chars;
	*i = *i + 1;
	return (*print_len);
}

int	no_conversion(int *print_len, const char str)
{
	int		nr_of_chars;

	nr_of_chars = ft_putchar(str);
	if (nr_of_chars == -1)
		return (-1);
	*print_len += nr_of_chars;
	return (*print_len);
}

int	conversion_type(va_list args, const char frmt)
{
	if (frmt == 'c')
		return (ft_putchar(va_arg(args, int)));
	// else if (frmt == 's')
	// 	return (ft_putstr(va_arg(args, char *)));
	// else if (frmt == 'p')
	// 	return (ft_put_ptr(va_arg(args, void *)));
	else if (frmt == 'd' || frmt == 'i')
		return (ft_put_nmbr(va_arg(args, int)));
	// else if (frmt == 'u')
	// 	return (ft_put_nmbr_unsigned(va_arg(args, unsigned int)));
	// else if (frmt == 'x')
	// 	return (ft_put_nmbr_hex_lower(va_arg(args, unsigned int)));
	// else if (frmt == 'X')
	// 	return (ft_put_nmbr_hex_upper(va_arg(args, unsigned int)));
	// else if (frmt == '%')
	// 	return (ft_putchar('%'));
	else
		return (-1);
}

int	main(void)
{
	// printf("%s\n", " === === === === === === === === === no format");
	// printf("return ft: %d\n", ft_printf(""));
	// printf("return st: %d\n", printf(""));
	// printf("return ft: %d\n", ft_printf("\x01\x02\a\v\b\f\r\n"));
	// printf("return st: %d\n", printf("\x01\x02\a\v\b\f\r\n"));
	// printf("return ft: %d\n", ft_printf("  abc 123 "));
	// printf("return st: %d\n", printf("  abc 123 "));
	// printf("%s\n", " === === === === === === === === === % format");
	// printf("return ft: %d\n", ft_printf("%%d"));
	// printf("return st: %d\n", printf("%%d"));
	// printf("return ft: %d\n", ft_printf(" %%"));
	// printf("return st: %d\n", printf(" %%"));
	// printf("return ft: %d\n", ft_printf("%%c"));
	// printf("return st: %d\n", printf("%%c"));
	// printf("return ft: %d\n", ft_printf("%%%%%%"));
	// printf("return st: %d\n", printf("%%%%%%"));
	// printf("return ft: %d\n", ft_printf("%%%c", 'x'));
	// printf("return st: %d\n", printf("%%%c", 'x'));
	// printf("%s\n", " === === === === === === === === === c format");
	// printf("return st: %d\n", printf(" %s %s ", " - ", ""));
	// printf("return ft: %d\n", ft_printf(" %s %s ", " - ", ""));
	// printf("return st: %d\n", printf(" %s %s %s %s %s", " - ", "", "4", "", "s2"));
	// printf("return ft: %d\n", ft_printf(" %s %s %s %s %s", " - ", "", "4", "", "s2"));
	// ft_printf("%c\n", 'x');
	// printf("%c\n", 'x');
	// ft_printf(" %c\n", 'x');
	// printf(" %c\n", 'x');
	// ft_printf("%c \n", 'x');
	// printf("%c \n", 'x');
	// ft_printf("%c   %d\n", 'x', 2);
	// printf("%c   %d\n", 'x', 2);
	// ft_printf("%c%c%c\n", 'a', '\t', 'b');
	// printf("%c%c%c\n", 'a', '\t', 'b');
	// ft_printf("%cc%cc%c\n", 'a', '\t', 'b');
	// printf("%cc%cc%c\n", 'a', '\t', 'b');
	// ft_printf("%cs%cs%c\n", 'c', 'b', 'a');
	// printf("%cs%cs%c\n", 'c', 'b', 'a');
	// printf("%s\n", " === === === === === === === === === s format");
	// printf("return ft: %d\n", ft_printf("%s\n", ""));
	// printf("return st: %d\n", printf("%s\n", ""));
	// printf("return ft: %d\n", ft_printf("%s\n", (char *) NULL));
	// printf("return st: %d\n", printf("%s\n", (char *) NULL));
	// printf("return ft: %d\n", ft_printf("%s\n", "some string with %s hehe"));
	// printf("return st: %d\n", printf("%s\n", "some string with %s hehe"));
	// printf("return ft: %d\n", ft_printf(" %s\n", "can it handle \t and \n?"));
	// printf("return st: %d\n", printf(" %s\n", "can it handle \t and \n?"));
	// printf("return ft: %d\n", ft_printf("%sx\n", "{} al$#@@@^&$$^#^@@^$*((&"));
	// printf("return st: %d\n", printf("%sx\n", "{} al$#@@@^&$$^#^@@^$*((&"));
	// printf("return ft: %d\n", ft_printf("%s%s%s\n", "And ", "some", "joined"));
	// printf("return st: %d\n", printf("%s%s%s\n", "And ", "some", "joined"));
	// printf("return ft: %d\n", ft_printf("%ss%ss%ss\n", "And ", "some other", "joined"));
	// printf("return st: %d\n", printf("%ss%ss%ss\n", "And ", "some other", "joined"));
	// printf("%s\n", " === === === === === === === === === p format");
	// ft_printf("%p\n", "");
	// printf("%p\n", "");
	// ft_printf("%p\n", NULL);
	// printf("%p\n", NULL);
	// ft_printf("%p\n", (void *)-14523);
	// printf("%p\n", (void *)-14523);
	// ft_printf("0x%p-\n", (void *)ULONG_MAX);
	// printf("0x%p-\n", (void *)ULONG_MAX);
	// ft_printf("%pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	// printf("%pp%p%p\n", (void *)LONG_MAX + 423856, (void *)0, (void *)INT_MAX);
	// printf("%s\n", " === === === === === === === === === d format");

	// printf("return ft: %d\n", ft_printf("%d\n", 0));
	// printf("return st: %d\n", printf("%d\n", 0));

	// printf("return ft: %d\n", ft_printf("%d\n", -10));
	// printf("return st: %d\n", printf("%d\n", -10));

	// printf("return ft: %d\n", ft_printf("%d\n", -200000));
	// printf("return st: %d\n", printf("%d\n", -200000));

	// printf("return ft: %d\n", ft_printf("%d\n", -6000023));
	// printf("return st: %d\n", printf("%d\n", -6000023));

	// printf("return ft: %d\n", ft_printf("%d\n", 10));
	// printf("return st: %d\n", printf("%d\n", 10));

	// printf("return ft: %d\n", ft_printf("%d\n", 10000));
	// printf("return st: %d\n", printf("%d\n", 10000));

	// printf("return ft: %d\n", ft_printf("%d\n", 100023));
	// printf("return st: %d\n", printf("%d\n", 100023));

	// printf("return ft: %d\n", ft_printf("%d\n", INT_MAX));
	// printf("return st: %d\n", printf("%d\n", INT_MAX));

	// printf("return ft: %d\n", ft_printf("%d\n", INT_MIN));
	// printf("return st: %d\n", printf("%d\n", INT_MIN));

	// printf("return ft: %d\n", ft_printf("dgs%dxx\n", 10));
	// printf("return st: %d\n", printf("dgs%dxx\n", 10));

	// printf("return ft: %d\n", ft_printf("%d%dd%d\n", 1, 2, -3));
	// printf("return st: %d\n", printf("%d%dd%d\n", 1, 2, -3));

	printf("%s\n", " === === === === === === === === === i format");
	ft_printf("%i\n", 0);
	printf("%i\n", 0);
	ft_printf("%i\n", -10);
	printf("%i\n", -10);
	ft_printf("%i\n", -200000);
	printf("%i\n", -200000);
	ft_printf("%i\n", -6000023);
	printf("%i\n", -6000023);
	ft_printf("%i\n", 10);
	printf("%i\n", 10);
	ft_printf("%i\n", 10000);
	printf("%i\n", 10000);
	ft_printf("%i\n", 100023);
	printf("%i\n", 100023);
	ft_printf("%i\n", INT_MAX);
	printf("%i\n", INT_MAX);
	ft_printf("%i\n", INT_MIN);
	printf("%i\n", INT_MIN);
	ft_printf("dgs%ixx\n", 10);
	printf("dgs%ixx\n", 10);
	ft_printf("%i%ii%i\n", 1, 2, -3);
	printf("%i%ii%i\n", 1, 2, -3);
	// printf("%s\n", " === === === === === === === === === u format");
	// ft_printf("%u\n", 0);
	// printf("%u\n", 0);
	// ft_printf("%u\n", -10);
	// ft_printf("%u\n", -10);
	// ft_printf("%u\n", -200000);
	// ft_printf("%u\n", -200000);
	// ft_printf("%u\n", -6000023);
	// ft_printf("%u\n", -6000023);
	// ft_printf("%u\n", 10);
	// printf("%u\n", 10);
	// ft_printf("%u\n", 10000);
	// printf("%u\n", 10000);
	// ft_printf("%u\n", 100023);
	// printf("%u\n", 100023);
	// ft_printf("%u\n", INT_MAX);
	// printf("%u\n", INT_MAX);
	// ft_printf("%u\n", INT_MIN);
	// printf("%u\n", INT_MIN);
	// ft_printf("%u\n", UINT_MAX);
	// printf("%u\n", UINT_MAX);
	// ft_printf("dgs%uxx\n", 10);
	// printf("dgs%uxx\n", 10);
	// ft_printf("%u%uu%u\n", 1, 2, -3);
	// printf("%u%uu%u\n", 1, 2, -3);
	// printf("%s\n", " === === === === === === === === === x format");
	// ft_printf("%x\n", 0);
	// printf("%x\n", 0);
	// ft_printf("%x\n", -10);
	// printf("%x\n", -10);
	// ft_printf("%x\n", -200000);
	// printf("%x\n", -200000);
	// ft_printf("%x\n", -6000023);
	// printf("%x\n", -6000023);
	// ft_printf("%x\n", 10);
	// printf("%x\n", 10);
	// ft_printf("%x\n", 10000);
	// printf("%x\n", 10000);
	// ft_printf("%x\n", 100023);
	// printf("%x\n", 100023);
	// ft_printf("%x\n", 0xabcdef);
	// printf("%x\n", 0xabcdef);
	// ft_printf("%x\n", 0x7fedcba1);
	// printf("%x\n", 0x7fedcba1);
	// ft_printf("%x\n", INT_MAX);
	// printf("%x\n", INT_MAX);
	// ft_printf("%x\n", INT_MIN);
	// printf("%x\n", INT_MIN);
	// ft_printf("%x\n", UINT_MAX);
	// printf("%x\n", UINT_MAX);
	// ft_printf("dgs%xxx\n", 10);
	// printf("dgs%xxx\n", 10);
	// ft_printf("%x%xx%x\n", 1, 2, -3);
	// printf("%x%xx%x\n", 1, 2, -3);
	// printf("%s\n", " === === === === === === === === === X format");
	// ft_printf("%X\n", 0);
	// printf("%X\n", 0);
	// ft_printf("%X\n", -10);
	// printf("%X\n", -10);
	// ft_printf("%X\n", -200000);
	// printf("%X\n", -200000);
	// ft_printf("%X\n", -6000023);
	// printf("%X\n", -6000023);
	// ft_printf("%X\n", 10);
	// printf("%X\n", 10);
	// ft_printf("%X\n", 10000);
	// printf("%X\n", 10000);
	// ft_printf("%X\n", 100023);
	// printf("%X\n", 100023);
	// ft_printf("%X\n", 0xabcdef);
	// printf("%X\n", 0xabcdef);
	// ft_printf("%X\n", 0x7fedcba1);
	// printf("%X\n", 0x7fedcba1);
	// ft_printf("%X\n", INT_MAX);
	// printf("%X\n", INT_MAX);
	// ft_printf("%X\n", INT_MIN);
	// printf("%X\n", INT_MIN);
	// ft_printf("%X\n", UINT_MAX);
	// printf("%X\n", UINT_MAX);
	// ft_printf("dgs%Xxx\n", 10);
	// printf("dgs%Xxx\n", 10);
	// ft_printf("%X%Xx%X\n", 1, 2, -3);
	// printf("%X%Xx%X\n", 1, 2, -3);

	// system("leaks a.out");
	return (0);
}
