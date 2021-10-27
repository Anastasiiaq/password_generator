#include "password_generator.h"

static char	find_max(t_edit_passwd edit_symb)
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

static char	*get_position(char *passwd, char symb_replace)
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

static void	lower_count_value(char replace, t_edit_passwd *edit_symb)
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

static void	increase_count_value(char symb, t_edit_passwd *edit_symb)
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

static void	replace_symb(char *passwd, char symb_replace, char symb_type)
{
	char	*symb;
	char	*symb_addr;
	
	if (symb_type == 'a')
		symb = get_symb(random_num(symb_replace, symb_type), 'a');
	else if (symb_type == 'A')
		symb = get_symb(random_num(symb_replace, symb_type), 'A');
	else if (symb_type == '1')
		symb = get_symb(random_num(symb_replace, '1'), '1');
	else
		symb = get_symb(random_num(symb_replace, '!'), '!');
	symb_addr = get_position(passwd, symb_replace);
	if (symb_addr[0] == symb_addr[1])
	{
		free(symb);
		replace_symb(passwd, symb_replace, symb_type);
		return ;
	}
	*symb_addr = symb[0];
	free(symb);
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
