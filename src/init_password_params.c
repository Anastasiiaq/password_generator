#include "password_generator.h"

void	new_params(t_param **passwd_params)
{
	*passwd_params = (t_param *)malloc(sizeof(t_param));
	if (!(*passwd_params))
		sys_call_err();
}

void	init_passwd_params(t_param *passwd_params)
{
	passwd_params->count_symb = 0;
	passwd_params->lowercase_letter = -1;
	passwd_params->uppercase_letter = -1;
	passwd_params->num = -1;
	passwd_params->special_symb = -1;
	passwd_params->count_params = 0;
	passwd_params->dflt = 0;
}
