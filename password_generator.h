#ifndef password_generator_h
#define password_generator_h

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

int	check_correct_password(char *passwd, t_param *passwd_params);

#endif /* password_generator_h */
