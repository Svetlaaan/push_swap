#include "push_swap.h"

int     check_char(char c)
{
	if ((c >= '0' && c <= '9') || c == '-')
		return (1);
	return (0);
}