#include "password_generator.h"

void	sys_call_err(void)
{
	fputs("\n\033[1;31mError:\033[0m ", stdout);
	puts(strerror(errno));
	puts("");
	exit(-1);
}

void	arg_is_num_err(void)
{
	puts("\n\033[1;31mError:\033[0m non-numeric argument!\n");
	exit(-1);
}

void	param_err(void)
{
	puts("\n\033[1;31mError:\033[0m invalid password parameters!\n");
	exit(-1);
}
