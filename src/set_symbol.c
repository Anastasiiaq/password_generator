#include "password_generator.h"

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

static void	set_base_val(char *base, char symb_type)
{
	char	*symb;
	
	if (symb_type == 'a')
		symb = "abcdefghijklmnopqrstuvwxyz";
	else if (symb_type == 'A')
		symb = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	else if (symb_type == '1')
		symb = "0123456789";
	else
		symb = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";
	while (*symb != '\0')
	{
		*base = *symb;
		base++;
		symb++;
	}
	*base = '\0';
}

static char	*get_base(char symb_type)
{
	char	*base;
	
	if (symb_type == 'a' || symb_type == 'A')
		base = (char *)malloc(sizeof(char) * (26 + 1));
	else if (symb_type == '1')
		base = (char *)malloc(sizeof(char) * (10 + 1));
	else
		base = (char *)malloc(sizeof(char) * (32 + 1));
	if (!base)
		sys_call_err();
	set_base_val(base, symb_type);
	return (base);
}

char	*get_symb(long int index, char symb_type)
{
	char	*base;
	char	*symb;
	
	if (symb_type == 'a')
		base = get_base('a');
	else if (symb_type == 'A')
		base = get_base('A');
	else if (symb_type == '1')
		base = get_base('1');
	else
		base = get_base('@');
	symb = (char *)malloc(sizeof(char) * 2);
	if (!symb)
		sys_call_err();
	symb[0] = base[index];
	symb[1] = '\0';
	free(base);
	return (symb);
}

void	set_symb(char *passwd, int iteration, char symb_type)
{
	char	*symb;
	
	if (symb_type == 'a')
		symb = get_symb(random_num(iteration + 1, symb_type), 'a');
	else if (symb_type == 'A')
		symb = get_symb(random_num(iteration + 1, symb_type), 'A');
	else if (symb_type == '1')
		symb = get_symb(random_num(iteration + 1, symb_type), '1');
	else
		symb = get_symb(random_num(iteration + 1, symb_type), '@');
	if (strlen(passwd) > 0 && passwd[iteration - 1] == symb[0])
	{
		free(symb);
		set_symb(passwd, iteration, symb_type);
		return ;
	}
	strcat(passwd, symb);
	free(symb);
}
