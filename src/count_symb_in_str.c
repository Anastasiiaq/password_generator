#include "password_generator.h"

static int	count_lowercase(char *str)
{
	int	count;
	
	count = 0;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
			count++;
		str++;
	}
	return (count);
}

static int	count_uppercase(char *str)
{
	int	count;
	
	count = 0;
	while (*str != '\0')
	{
		if (*str >= 'A' && *str <= 'Z')
			count++;
		str++;
	}
	return (count);
}

static int	count_num(char *str)
{
	int	count;
	
	count = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			count++;
		str++;
	}
	return (count);
}

static int	count_special_symb(char *str)
{
	int	count;
	
	count = 0;
	while (*str != '\0')
	{
		if ((*str >= '!' && *str <= '/') || (*str >= ':' && *str <= '@')
			|| (*str >= '[' && *str <= '`') || (*str >= '{' && *str <= '~'))
			count++;
		str++;
	}
	return (count);
}

void	count_symb_in_str(char *str, t_edit_passwd *count_symb, t_param passwd_params)
{
	if (passwd_params.lowercase_letter != -1)
		count_symb->count_lowercase = count_lowercase(str);
	if (passwd_params.uppercase_letter != -1)
		count_symb->count_uppercase = count_uppercase(str);
	if (passwd_params.num != -1)
		count_symb->count_num = count_num(str);
	if (passwd_params.special_symb != -1)
		count_symb->count_special_symb = count_special_symb(str);
}
