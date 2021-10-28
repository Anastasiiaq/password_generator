#include "password_generator.h"

static void	init_edit_passwd_struct(t_edit_passwd *edit_passwd_struct)
{
	edit_passwd_struct->count_lowercase = -1;
	edit_passwd_struct->count_uppercase = -1;
	edit_passwd_struct->count_num = -1;
	edit_passwd_struct->count_special_symb = -1;
}

void	edit_password(char **passwd, t_param *passwd_params)
{
	static t_edit_passwd	edit_symb;
	
	if (edit_symb.count_lowercase == 0 && edit_symb.count_uppercase == 0 && edit_symb.count_num == 0 && edit_symb.count_special_symb == 0)
	{
		init_edit_passwd_struct(&edit_symb);
		count_symb_in_str(*passwd, &edit_symb, *passwd_params);
	}
	if (edit_symb.count_lowercase == 0)
		replace_with_symb(*passwd, &edit_symb, 'a');
	if (edit_symb.count_uppercase == 0)
		replace_with_symb(*passwd, &edit_symb, 'A');
	if (edit_symb.count_num == 0)
		replace_with_symb(*passwd, &edit_symb, '1');
	if (edit_symb.count_special_symb == 0)
		replace_with_symb(*passwd, &edit_symb, '@');
	if (check_correct_password(*passwd, *passwd_params))
		edit_password(passwd, passwd_params);
}
