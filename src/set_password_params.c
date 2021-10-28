#include "password_generator.h"

static int	arg_is_num(char *argv)
{
	while (*argv != '\0')
	{
		if (isdigit(*argv) == 0)
			return (-1);
		argv++;
	}
	return (0);
}

static void	check_max_passwd_length(char *argv)
{
	if (strlen(argv) >= strlen("1000000") && strcmp(argv, "1000000") > 0)
		param_err();
}

void	set_param(char **argv, t_param *passwd_params)
{
	if (arg_is_num(argv[1]) != 0)
		param_err();
	check_max_passwd_length(argv[1]);
	passwd_params->count_symb = atoi(argv[1]);
	if (passwd_params->count_symb == 0)
		param_err();
	argv += 2;
	while (*argv != NULL)
	{
		if (strcmp(*argv, "-a") == 0 && passwd_params->lowercase_letter == -1)
			passwd_params->lowercase_letter = 1;
		else if (strcmp(*argv, "-A") == 0 && passwd_params->uppercase_letter == -1)
			passwd_params->uppercase_letter = 1;
		else if (strcmp(*argv, "-1") == 0 && passwd_params->num == -1)
			passwd_params->num = 1;
		else if (strcmp(*argv, "-@") == 0 && passwd_params->special_symb == -1)
			passwd_params->special_symb = 1;
		else
			param_err();
		argv++;
	}
}
