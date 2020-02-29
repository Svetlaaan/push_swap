#include "push_swap.h"

int 	sorting_four(t_what **storage)
{
	sort_by_blocks(&(*storage));
	if (sorting_two(&(*storage)) == 1)
	{
		while ((*storage)->stack_b > 0)
			push('a', &(*storage));
	}
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}

int 	sorting_two(t_what **storage)
{
	if ((*storage)->stack_b == 2)
	{
		if ((*storage)->head_b->index < (*storage)->tail_b->index)
			s_swap(&(*storage)->head_b, &(*storage), 'b');
	}
	if ((*storage)->stack_a == 2)
	{
		if ((*storage)->head_a->index > (*storage)->tail_a->index)
			s_swap(&(*storage)->head_a, &(*storage), 'a');
	}
	return (1); ////////////
}

int 	sorting_five(t_what **storage)
{
	sort_by_blocks(&(*storage));
	if (sorting_three(&(*storage)) == -1)
		return (-1);
	if ((*storage)->head_b->index < (*storage)->tail_b->index)
		s_swap(&(*storage)->head_b, &(*storage), 'b');
	while ((*storage)->stack_b > 0)
		push('a', &(*storage));
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}

int 	sorting_three(t_what **storage)
{
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	if ((*storage)->head_a->index > (*storage)->head_a->next->index && (*storage)->head_a->index < (*storage)->tail_a->index)
		s_swap(&(*storage)->head_a, &(*storage), 'a');
	else if ((*storage)->head_a->index > (*storage)->head_a->next->index && (*storage)->head_a->index > (*storage)->tail_a->index)
	{
		if ((*storage)->tail_a->index < (*storage)->tail_a->prev->index)
		{
			s_swap(&(*storage)->head_a, &(*storage), 'a');
			rr_reverse(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		else if ((*storage)->tail_a->index > (*storage)->tail_a->prev->index)
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	else if ((*storage)->head_a->index < (*storage)->head_a->next->index && (*storage)->tail_a->index < (*storage)->head_a->index)
		rr_reverse(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	else if ((*storage)->head_a->index < (*storage)->head_a->next->index && (*storage)->tail_a->index > (*storage)->head_a->index)
	{
		s_swap(&(*storage)->head_a, &(*storage), 'a');
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}

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

int 	sorting(t_what **storage)
{
	if ((*storage)->stack_a > 5)
	{
		sort_by_blocks(&(*storage));
		if (is_sorted((*storage)->head_b) == 1)
		{
			while ((*storage)->stack_b > 0)
			{
				push('a', &(*storage));
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
			}
		}
		else if ((*storage)->stack_b >= 2 && (*storage)->stack_b <= 3)
			s_swap(&(*storage)->head_b, &(*storage), 'b');
	}
	else if ((*storage)->stack_a == 3)
	{
			if (sorting_three(&(*storage)) == 1)
				return (1);
			else
				return (-1);
	}
	else if ((*storage)->stack_a == 5)
	{
			if (sorting_five(&(*storage)) == 1)
				return (1);
			else
				return (-1);
	}
	else if ((*storage)->stack_a == 2)
	{
		if (sorting_two(&(*storage)) == 1)
			return (1);
		else
			return (-1);
	}
	else if ((*storage)->stack_a == 4)
	{
		if (sorting_four(&(*storage)) == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}