#include "password_generator.h"

static int	check_lowercase_letter(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			return (0);
		str++;
	}
	return (1);
}

static int	check_uppercase_letter(char *str)
{
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
			return (0);
		str++;
	}
	return (1);
}

static int	check_num(char *str)
{
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			return (0);
		str++;
	}
	return (1);
}

static int	check_special_symb(char *str)
{
	while (*str != '\0')
	{
		if ((*str >= '!' && *str <= '/') || (*str >= ':' && *str <= '@')
			|| (*str >= '[' && *str <= '`') || (*str >= '{' && *str <= '~'))
			return (0);
		str++;
	}
	return (1);
}

int	check_correct_password(char *passwd, t_param *passwd_params)
{
	if (passwd_params->lowercase_letter != -1)
	{
		if (check_lowercase_letter(passwd) == 1)
			return (1);
	}
	if (passwd_params->uppercase_letter != -1)
	{
		if (check_uppercase_letter(passwd) == 1)
			return (1);
	}
	if (passwd_params->num != -1)
	{
		if (check_num(passwd) == 1)
			return (1);
	}
	if (passwd_params->special_symb != -1)
	{
		if (check_special_symb(passwd) == 1)
			return (1);
	}
	return (0);
}
