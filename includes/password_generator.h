#ifndef password_generator_h
#define password_generator_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/errno.h>

typedef struct s_param
{
	int	count_symb;
	int	lowercase_letter;
	int	uppercase_letter;
	int	num;
	int	special_symb;
	int	count_params;
	int	dflt;
}				t_param;

typedef struct s_edit_passwd
{
	int	count_lowercase;
	int	count_uppercase;
	int	count_num;
	int	count_special_symb;
}				t_edit_passwd;

/* check_correct_password.c */
int			check_correct_password(char *passwd, t_param passwd_params);

/* count_symb_in_str.c */
void		count_symb_in_str(char *str, t_edit_passwd *count_symb, t_param passwd_params);

/* set_symbol.c */
long int	random_num(int mult, char symb);
char		*get_symb(long int index, char symb_type);
void		set_symb(char *passwd, int iteration, char symb_type);

/* replace_symbol.c */
void		replace_with_symb(char *passwd, t_edit_passwd *edit_symb, char symb_type);

/* edit_password.c */
void		edit_password(char **passwd, t_param *passwd_params);

/* create_password.c */
void		create_password(char **passwd, t_param *passwd_params);

/* init_password_params.c */
void		new_params(t_param **passwd_params);
void		init_passwd_params(t_param *passwd_params);

/* set_password_params.c */
void	set_param(char **argv, t_param *passwd_params);

/* errors.c */
void		sys_call_err(void);
void		param_err(void);

#endif
