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

int 	is_sorted_rev(t_num *head)
{
	t_num	*tmp;
	int 	prev_index;

	tmp = head->next;
	prev_index = head->index;
	while (tmp)
	{
		if (prev_index < tmp->index)
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

int 	main_sort(t_what **storage)
{
	sort_by_blocks(&(*storage));
	if ((*storage)->stack_b == 3 || (*storage)->stack_a == 3)
	{
		sorting_three(&(*storage));
		while ((*storage)->stack_b > 0)
		{
			push('a', &(*storage));
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		if ((*storage)->head_a->index == (*storage)->tail_a->index - 1)
		{
			while ((*storage)->head_a->podblock == 1)
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		else
		{
			s_swap(&(*storage)->head_a, &(*storage), 'a');
			while ((*storage)->head_a->podblock == 1)
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage)); /////// закончила тут!
		}
	}
	else
	{
		set_block(&(*storage));
		sort_by_blocks(&(*storage));
		sorting(&(*storage));
	}

	return (1);
}
// делить стэк B пока чисел не будет меньше 4 //

int len_of_block(t_what **storage, int num)
{
	t_num *tmp;
	int len = 0;

	tmp = (*storage)->head_a;
	while (tmp)
	{
		if (tmp->block == num)
			len += 1;
		tmp = tmp->next;
	}
	tmp = (*storage)->head_b;
	while (tmp)
	{
		if (tmp->block == num)
			len += 1;
		tmp = tmp->next;
	}
	return (len);
}

int 	sorting(t_what **storage)
{
	if ((*storage)->stack_a > 5)
		main_sort(&(*storage));
	else if ((*storage)->stack_a == 3)
	{
			if (sorting_three(&(*storage)) == 1)
				return (1);
			return (-1);
	}
	else if ((*storage)->stack_a == 5)
	{
			if (sorting_five(&(*storage)) == 1)
				return (1);
			return (-1);
	}
	else if ((*storage)->stack_a == 2)
	{
		if (sorting_two(&(*storage)) == 1)
			return (1);
		return (-1);
	}
	else if ((*storage)->stack_a == 4)
	{
		if (sorting_four(&(*storage)) == 1)
			return (1);
		return (-1);
	}
	return (0);
}