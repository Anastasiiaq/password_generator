#include "password_generator.h"

void	error_allocation()
{
	puts("Error: memory allocation");
	exit(-1);
}

void	new_params(t_param **passwd_params)
{
	*passwd_params = (t_param *)malloc(sizeof(t_param));
	if (!(*passwd_params))
		error_allocation();
}

void	init_passwd_params(t_param *passwd_params)
{
	passwd_params->count_symb = 0;
	passwd_params->lowercase_letter = -1;
	passwd_params->uppercase_letter = -1;
	passwd_params->num = -1;
	passwd_params->special_symb = -1;
	passwd_params->count_params = 0;
}

void	get_count_param(int argc, t_param *passwd_params)
{
	passwd_params->count_params = argc - 1;
}

int	arg_is_num(char *argv)
{
	while (*argv != '\0')
	{
		if (isdigit(*argv) == 0)
			return (-1);
		argv++;
	}
	return (0);
}

void	arg_is_num_err()
{
	puts("Error: non-numeric argument");
	exit(-1);
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
		if (**argv == 'a')
			passwd_params->lowercase_letter = 1;
		else if (**argv == 'A')
			passwd_params->uppercase_letter = 1;
		else if (**argv == '1')
			passwd_params->num = 1;
		else if (**argv == '!')
			passwd_params->special_symb = 1;
		argv++;
	}
}

void	set_order_num(t_param *passwd_params)
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

void	new_passwd(char **passwd, t_param passwd_params)
{
	*passwd = (char *)calloc(sizeof(char) * (passwd_params.count_symb + 1), 0);
	if (!(*passwd))
		error_allocation();
}

long int	random_num(int mult, char symb)
{
	long int	num;
	
	srandom(mult * getpid() + (unsigned int)random());
	if (symb == 'a' || symb == 'A')
		num = random() % 26;
	else if (symb == '1')
		num = random() % 10;
	else
		num = random() % 32;
	return (num);
}

long int	random_order_num(t_param passwd_params)
{
	long int num;
	
	srandom(passwd_params.count_params * getpid() + (unsigned int)random());
	num = random() % (passwd_params.count_params - 1);
	return (num);
}

char	*get_num_symb(long int index)
{
	char	*base;
	char	*symb;
	
	base = "0123456789";
	symb = (char *)malloc(sizeof(char) * 2);
	symb[0] = base[index];
	symb[1] = '\0';
	return (symb);
}

char	*get_lowercase_symb(long int index)
{
	char	*base;
	char	*symb;
	
	base = "abcdefghijklmnopqrstuvwxyz";
	symb = (char *)malloc(sizeof(char) * 2);			// проверка маллока
	symb[0] = base[index];
	symb[1] = '\0';
	return (symb);
}

char	*get_uppercase_symb(long int index)
{
	char	*base;
	char	*symb;

	base = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	symb = (char *)malloc(sizeof(char) * 2);			// проверка маллока
	symb[0] = base[index];
	symb[1] = '\0';
	return (symb);
}

char	*get_special_symb(long int index)
{
	char	*base;
	char	*symb;
	
	base =  "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	symb = (char *)malloc(sizeof(char) * 2);
	symb[0] = base[index];
	symb[1] = '\0';
	return (symb);
}

void	set_symb(char *passwd, int iteration, char symb_type)
{
	char		*symb;
	
	if (symb_type == 'a')
		symb = get_lowercase_symb(random_num(iteration + 1, symb_type));
	else if (symb_type == 'A')
		symb = get_uppercase_symb(random_num(iteration + 1, symb_type));
	else if (symb_type == '1')
		symb = get_num_symb(random_num(iteration + 1, symb_type));
	else
		symb = get_special_symb(random_num(iteration + 1, symb_type));
	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
	{
		free(symb);
		set_symb(passwd, iteration, symb_type);
		return ;
	}
	strcat(passwd, symb);
	free(symb);
}

void	create_password(char **passwd, t_param *passwd_params)
{
	long int	rand_ord_num;
	int		i;

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
			set_symb(*passwd, i, '!');
		i++;
	}
}

void	init_edit_passwd_struct(t_edit_passwd *edit_passwd_struct)
{
	edit_passwd_struct->count_lowercase = -1;
	edit_passwd_struct->count_uppercase = -1;
	edit_passwd_struct->count_num = -1;
	edit_passwd_struct->count_special_symb = -1;
}

char	find_max(t_edit_passwd edit_symb)
{
	if (edit_symb.count_lowercase >= edit_symb.count_uppercase
		&& edit_symb.count_lowercase >= edit_symb.count_num
		&& edit_symb.count_lowercase >= edit_symb.count_special_symb)
		return ('a');
	else if (edit_symb.count_uppercase >= edit_symb.count_lowercase
		&& edit_symb.count_uppercase >= edit_symb.count_num
		&& edit_symb.count_uppercase >= edit_symb.count_special_symb)
		return ('A');
	else if (edit_symb.count_num >= edit_symb.count_uppercase
		&& edit_symb.count_num >= edit_symb.count_lowercase
		&& edit_symb.count_num >= edit_symb.count_special_symb)
		return ('1');
	else
		return ('!');
}

char	*get_position(char *passwd, char symb_replace)
{
	if (symb_replace == 'a')
	{
		while (*passwd != '\0' && !(*passwd >= 'a' && *passwd <= 'z'))
			passwd++;
	}
	else if (symb_replace == 'A')
	{
		while (*passwd != '\0' && !(*passwd >= 'A' && *passwd <= 'Z'))
			passwd++;
	}
	else if (symb_replace == '1')
	{
		while (*passwd != '\0' && !(*passwd >= '0' && *passwd <= '9'))
			passwd++;
	}
	else if (symb_replace == '!')
	{
		while (*passwd != '\0' && !((*passwd >= '!' && *passwd <= '/')
			|| (*passwd >= ':' && *passwd <= '@')
				|| (*passwd >= '[' && *passwd <= '`')
					|| (*passwd >= '{' && *passwd <= '~')))
			passwd++;
	}
	return (passwd);
}

//void	replace_letter_symb(char *passwd, char symb_replace, char letter_type)
//{
//	long int	num;
//	char		*symb;
//	char		*symb_addr;
//
//	num = random_num(symb_replace, letter_type);
//	if (letter_type == 'a')
//		symb = get_lowercase_symb(num);
//	else
//		symb = get_uppercase_symb(num);
//	symb_addr = get_position(passwd, symb_replace);
////	if (passwd != symb_addr && (*symb_addr == *(symb_addr - 1) || *symb_addr == *(symb_addr + 1)))
////	{
////		free(symb);
////		replace_letter_symb(passwd, symb_replace, letter_type);
////		return ;
////	}
//	*symb_addr = symb[0];
//	free(symb);
//}

void	lower_count_value(char replace, t_edit_passwd *edit_symb)
{
	if (replace == 'a')
		edit_symb->count_lowercase--;
	else if (replace == 'A')
		edit_symb->count_uppercase--;
	else if (replace == '1')
		edit_symb->count_num--;
	else if (replace == '!')
		edit_symb->count_special_symb--;
}

void	replace_symb(char *passwd, char symb_replace, char symb_type)
{
	char		*symb;
	char		*symb_addr;
	
	if (symb_type == 'a')
		symb = get_lowercase_symb(random_num(symb_replace, symb_type));
	else if (symb_type == 'A')
		symb = get_uppercase_symb(random_num(symb_replace, symb_type));
	else if (symb_type == '1')
		symb = get_num_symb(random_num(symb_replace, '1'));
	else
		symb = get_special_symb(random_num(symb_replace, '!'));
	symb_addr = get_position(passwd, symb_replace);
//	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
//	{
//		free(symb);
//		set_num_symb(passwd, iteration);
//		return ;
//	}
	*symb_addr = symb[0];
	free(symb);
}

void	increase_count_value(char symb, t_edit_passwd *edit_symb)
{
	if (symb == 'a')
		edit_symb->count_lowercase++;
	else if (symb == 'A')
		edit_symb->count_uppercase++;
	else if (symb == '1')
		edit_symb->count_num++;
	else if (symb == '!')
		edit_symb->count_special_symb++;
}

void	replace_with_symb(char *passwd, t_edit_passwd *edit_symb, char symb_type)
{
	char	symb_max;
	
	symb_max = find_max(*edit_symb);
	if (symb_type == 'a')
		replace_symb(passwd, symb_max, 'a');
	else if (symb_type == 'A')
		replace_symb(passwd, symb_max, 'A');
	else if (symb_type == '1')
		replace_symb(passwd, symb_max, '1');
	else
		replace_symb(passwd, symb_max, '!');
	increase_count_value(symb_type, edit_symb);
	lower_count_value(symb_max, edit_symb);
}

void	edit_password(char **passwd, t_param *passwd_params)
{
	static t_edit_passwd	edit_symb;
	
	init_edit_passwd_struct(&edit_symb);
	count_symb_in_str(*passwd, &edit_symb, *passwd_params);
	if (edit_symb.count_lowercase == 0)
		replace_with_symb(*passwd, &edit_symb, 'a');
	if (edit_symb.count_uppercase == 0)
		replace_with_symb(*passwd, &edit_symb, 'A');
	if (edit_symb.count_num == 0)
		replace_with_symb(*passwd, &edit_symb, '1');
	if (edit_symb.count_special_symb == 0)
		replace_with_symb(*passwd, &edit_symb, '!');
	if (check_correct_password(*passwd, *passwd_params))
		edit_password(passwd, passwd_params);
}

void	print_passwd(char *passwd, t_param *passwd_params)
{
	puts("Generated password:");
	puts(passwd);
}

void	check_correct_param(t_param passwd_params)
{
	if (passwd_params.count_symb < passwd_params.count_params - 1)
	{
		puts("Error: The password length is too small for the specified parameters!");
		exit(-1);
	}
}

int main(int argc, char **argv)
{
	t_param	*passwd_params;
	char	*passwd;
	
	if (argc >= 3 && argc <= 6)
	{
		new_params(&passwd_params);
		init_passwd_params(passwd_params);
		get_count_param(argc, passwd_params);
		set_param(argv, passwd_params);
		check_correct_param(*passwd_params);
		create_password(&passwd, passwd_params);
		if (check_correct_password(passwd, *passwd_params))
			edit_password(&passwd, passwd_params);
		print_passwd(passwd, passwd_params);
	}
	else if (argc < 3)
		puts("Error: too few arguments");
	else
		puts("Error: too many arguments");
	
	return 0;
}
