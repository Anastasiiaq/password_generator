#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

typedef struct s_param
{
	int	count_symb;
	int	lowercase_letter;
	int	uppercase_letter;
	int	num;
	int special_symb;
	int	count_params;
}				t_param;

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

void	new_passwd(char **passwd, t_param *passwd_params)
{
	*passwd = (char *)calloc(sizeof(char) * (passwd_params->count_symb + 1), 0);
	if (!(*passwd))
		error_allocation();
}

long int	random_order_num(t_param *passwd_params)
{
	long int num;
	
	srandom(passwd_params->count_params * getpid() + (unsigned int)random());
	num = random() % (passwd_params->count_params - 1);
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

void	set_num_symb(char *passwd, int iteration)
{
	long int	num;
	char		*symb;
	
	srandom((iteration + 1) * getpid() + (unsigned int)random());
	num = random() % 10;
	symb = get_num_symb(num);
	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
	{
//		free(symb);
		set_num_symb(passwd, iteration);
//		return ;
	}
	strcat(passwd, symb);
	free(symb);
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

void	set_letter_symb(char *passwd, int iteration, char letter_type)
{
	long int	num;
	char		*symb;
	
	srandom((iteration + 1) * getpid() + (unsigned int)random());
	num = random() % 26;
	if (letter_type == 'a')
		symb = get_lowercase_symb(num);
	else
		symb = get_uppercase_symb(num);
	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
		set_letter_symb(passwd, iteration, letter_type);
	strcat(passwd, symb);
	free(symb);
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

void	set_special_symb(char *passwd, int iteration)
{
	long int	num;
	char		*symb;
	
	srandom((iteration + 1) * getpid() + (unsigned int)random());
	num = random() % 32;
	symb = get_special_symb(num);
	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
	{
//		free(symb);
		set_special_symb(passwd, iteration);
//		return ;
	}
	strcat(passwd, symb);
	free(symb);
}


void	print_passwd(t_param *passwd_params)
{
	char	*passwd;
//	char	*symb;
	long int	rand_ord_num;
	// tmp
	int		i;
//	long int num;
	
	
	set_order_num(passwd_params);
	
	new_passwd(&passwd, passwd_params);
	i = 0;
	while (i < passwd_params->count_symb)
	{
		rand_ord_num = random_order_num(passwd_params);
		if (passwd_params->lowercase_letter == rand_ord_num)
			set_letter_symb(passwd, i, 'a');
		else if (passwd_params->uppercase_letter == rand_ord_num)
			set_letter_symb(passwd, i, 'A');
		else if (passwd_params->num == rand_ord_num)
			set_num_symb(passwd, i);
		else if (passwd_params->special_symb == rand_ord_num)
			set_special_symb(passwd, i);
		i++;
	}
//	random_symb(passwd_params);
	
	
	
//	i = 0;
//	while (i < passwd_params->count_symb)
//	{
//		srandom((i + 1) * getpid() + (unsigned int)random());
//		num = random() % 10;
//		symb = get_num_symb(num);
//		if (strlen(passwd) > 0 && passwd[i - 1] == symb[0])
//			continue ;
//		strcat(passwd, get_num_symb(num));
//		i++;
//	}
	puts("Generated password:");
	puts(passwd);
}

int main(int argc, char **argv)
{
	t_param	*passwd_params;
	
	if (argc >= 3 && argc <= 6)
	{
		new_params(&passwd_params);
		init_passwd_params(passwd_params);
		get_count_param(argc, passwd_params);
		set_param(argv, passwd_params);
		print_passwd(passwd_params);
	}
	else if (argc < 3)
		puts("Error: too few arguments");
	else
		puts("Error: too many arguments");
	
	return 0;
}
