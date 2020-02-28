#include "push_swap.h"

int		is_sorted_final(t_what *storage)
{
	t_num	*tmp;
	int 	prev_index;

	if (storage->head_b != NULL)
		return (-1);
	else if (storage->head_a == NULL)
		return (-1);
	tmp = storage->head_a->next;
	prev_index = storage->head_a->index;
	while (tmp)
	{
		if (prev_index > tmp->index)
			return (-1);
		prev_index = tmp->index;
		tmp = tmp->next;
	}
	return (1);
}

int 	is_sorted(t_num *head)
{
	t_num	*tmp;
	int 	prev_index;

	tmp = head->next;
	prev_index = head->index;
	while (tmp)
	{
		if (prev_index > tmp->index)
			return (-1);
		prev_index = tmp->index;
		tmp = tmp->next;
	}
	return (1);
}