#include "password_generator.h"

static void	new_passwd(char **passwd, t_param passwd_params)
{
	*passwd = (char *)calloc(sizeof(char), (passwd_params.count_symb + 1));
	if (!(*passwd))
		sys_call_err();
}

static void	set_order_num(t_param *passwd_params)
{
	int	num;
	
	num = 0;
	if (passwd_params->lowercase_letter == 1)
		passwd_params->lowercase_letter = num++;
	if (passwd_params->uppercase_letter == 1)
		passwd_params->uppercase_letter = num++;
	if (passwd_params->num == 1)
		passwd_params->num = num++;
	if (passwd_params->special_symb == 1)
		passwd_params->special_symb = num++;
}

static long int	random_order_num(t_param passwd_params)
{
	long int	num;
	
	srandom(passwd_params.count_params * getpid() + (unsigned int)random());
	num = random() % (passwd_params.count_params - 1);
	return (num);
}

void	create_password(char **passwd, t_param *passwd_params)
{
	long int	rand_ord_num;
	int			i;

	set_order_num(passwd_params);
	new_passwd(passwd, *passwd_params);
	i = 0;
	while (i < passwd_params->count_symb)
	{
		rand_ord_num = random_order_num(*passwd_params);
		if (passwd_params->lowercase_letter == rand_ord_num)
			set_symb(*passwd, i, 'a');
		else if (passwd_params->uppercase_letter == rand_ord_num)
			set_symb(*passwd, i, 'A');
		else if (passwd_params->num == rand_ord_num)
			set_symb(*passwd, i, '1');
		else if (passwd_params->special_symb == rand_ord_num)
			set_symb(*passwd, i, '@');
		i++;
	}
}
