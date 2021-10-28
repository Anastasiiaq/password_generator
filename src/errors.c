#include "password_generator.h"

void	sys_call_err(void)
{
	fputs("\n\033[1;31mError:\033[0m ", stdout);
	puts(strerror(errno));
	puts("");
	exit(-1);
}

void	passwd_length_err(void)
{
	puts("\n\033[1;31mError:\033[0m invalid password length value!\n");
	exit(-1);
}

void	param_err(char *flag)
{
	fputs("\n\033[1;31mError:\033[0m unknown argument: ", stdout);
	fputs("'", stdout);
	fputs(flag, stdout);
	puts("'");
	puts("");
	exit(-1);
}
