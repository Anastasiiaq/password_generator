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

void	init_passwd_params(t_param **passwd_params)
{
	(*passwd_params)->count_symb = 0;
	(*passwd_params)->lowercase_letter = 0;
	(*passwd_params)->uppercase_letter = 0;
	(*passwd_params)->num = 0;
	(*passwd_params)->special_symb = 0;
	(*passwd_params)->count_params = 0;
}

void	get_count_param(int argc, t_param **passwd_params)
{
	(*passwd_params)->count_params = argc - 1;
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

void	set_param(char **argv, t_param **passwd_params)
{
	if (arg_is_num(argv[1]) != 0)
		arg_is_num_err();
	(*passwd_params)->count_symb = atoi(argv[1]);
	if ((*passwd_params)->count_symb == 0)
		return ;
	argv += 2;
	while (*argv != NULL)
	{
		if (**argv == 'a')
			(*passwd_params)->lowercase_letter = 1;
		else if (**argv == 'A')
			(*passwd_params)->uppercase_letter = 1;
		else if (**argv == '1')
			(*passwd_params)->num = 1;
		else if (**argv == '!')
			(*passwd_params)->special_symb = 1;
		argv++;
	}
}

void	new_passwd(char **passwd, t_param *passwd_params)
{
	*passwd = (char *)malloc(sizeof(char) * (passwd_params->count_symb + 1));
	if (!(*passwd))
		error_allocation();
}

void	random_symb(t_param *passwd_params)
{
	long int num;
	
	srandom((unsigned int)time(NULL));
	num = random() % passwd_params->count_params;
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

void	print_passwd(t_param *passwd_params)
{
	char	*passwd;
	// tmp
	int		i;
	long int num;
	
	new_passwd(&passwd, passwd_params);
//	random_symb(passwd_params);
	
	i = 0;
	while (i < passwd_params->count_symb)
	{
		srandom(i * getpid() + (unsigned int)random());
		num = random() % 10;
		strcat(passwd, get_num_symb(num));
		i++;
	}
	passwd[i] = '\0';
	puts("Generated password:");
	puts(passwd);
}

int main(int argc, char **argv)
{
	t_param	*passwd_params;
	
	if (argc > 1)
	{
		new_params(&passwd_params);
		init_passwd_params(&passwd_params);
		get_count_param(argc, &passwd_params);
		set_param(argv, &passwd_params);
		print_passwd(passwd_params);
	}
	else
		puts("Too few arguments");
	return 0;
}
