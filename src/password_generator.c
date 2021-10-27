#include "password_generator.h"

void	print_passwd(char *passwd)
{
	puts("\nGenerated password:");
	fputs("\033[1;31m", stdout);
	puts(passwd);
	fputs("\033[0m", stdout);
	puts("");
}

void	get_count_param(int argc, t_param *passwd_params)
{
	passwd_params->count_params = argc - 1;
}

void	check_correct_param(t_param passwd_params)
{
	if (passwd_params.count_symb < passwd_params.count_params - 1)
	{
		puts("\n\033[1;31mError:\033[0m The password length is too small for the specified parameters!\n");
		exit(-1);
	}
}

void	help(void)
{
	puts("\nTo \033[35mgenerate a password\033[0m, enter:");
	puts("* number of symbols");
	puts("* 'a' - to use lowercase letters");
	puts("* 'A' - to use uppercase letters");
	puts("* '1' - to use numbers");
	puts("* '!' - to use special symbols\n");
	puts("\033[32mExample:\033[0m genpasswd 8 a A 1 !\n");
}

void	find_help(char **argv)
{
	while (*argv != NULL)
	{
		if (strcmp(*argv, "-help") == 0 || strcmp(*argv, "--help") == 0)
		{
			help();
			exit(0);
		}
		argv++;
	}
}

int main(int argc, char **argv)
{
	t_param	*passwd_params;
	char	*passwd;
	
	find_help(argv);
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
		print_passwd(passwd);
		free(passwd_params);
		free(passwd);
	}
	else if (argc < 3)
		puts("\n\033[1;31mError:\033[0m too few arguments\n");
	else
		puts("\n\033[1;31mError:\033[0m too many arguments\n");
	return 0;
}