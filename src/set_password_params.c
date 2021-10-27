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

void	set_param(char **argv, t_param *passwd_params)
{
	if (arg_is_num(argv[1]) != 0)
		arg_is_num_err();
	passwd_params->count_symb = atoi(argv[1]);
	if (passwd_params->count_symb == 0)
		return ;
	argv += 2;
	while (*argv != NULL)
	{
		if (**argv == 'a' && passwd_params->lowercase_letter == -1)
			passwd_params->lowercase_letter = 1;
		else if (**argv == 'A' && passwd_params->uppercase_letter == -1)
			passwd_params->uppercase_letter = 1;
		else if (**argv == '1' && passwd_params->num == -1)
			passwd_params->num = 1;
		else if (**argv == '!' && passwd_params->special_symb == -1)
			passwd_params->special_symb = 1;
		else
			param_err();
		argv++;
	}
}
