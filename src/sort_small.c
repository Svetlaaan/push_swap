#include "../inc/push_swap.h"

int 	sorting_two(t_what **storage)
{
	if ((*storage)->stack_b == 2)
	{
		if ((*storage)->head_b->index > (*storage)->tail_b->index)
			s_swap(&(*storage)->head_b, &(*storage), 'b');
		if (is_sorted((*storage)->head_b))
			return (1);
	}
	if ((*storage)->stack_a == 2)
	{
		if ((*storage)->head_a->index > (*storage)->tail_a->index)
			s_swap(&(*storage)->head_a, &(*storage), 'a');
		if (is_sorted((*storage)->head_a))
			return (1);
	}
	return (-1);
}

int 	sort_3_mov(t_what **storage, t_num **head_tmp, t_num **tail_tmp)
{
	if ((*storage)->curr_stack == 'A')
	{
		if (is_sorted((*storage)->head_a) == 1)
			return (1);
	}
	else if ((*storage)->curr_stack == 'B')
	{
		if (is_sorted((*storage)->head_b) == 1)
			return (1);
	}
	if ((*head_tmp)->index > (*head_tmp)->next->index && (*head_tmp)->index < (*tail_tmp)->index)
		s_swap(&(*head_tmp), &(*storage), 'a');
	else if ((*head_tmp)->index > (*head_tmp)->next->index && (*head_tmp)->index > (*tail_tmp)->index)
	{
		if ((*tail_tmp)->index < (*tail_tmp)->prev->index)
		{
			s_swap(&(*head_tmp), &(*storage), 'a');
			rr_reverse(&(*head_tmp), &(*tail_tmp), &(*storage));
		}
		else if ((*tail_tmp)->index > (*tail_tmp)->prev->index)
			r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
	}
	else if ((*head_tmp)->index < (*head_tmp)->next->index && (*tail_tmp)->index < (*head_tmp)->index)
		rr_reverse(&(*head_tmp), &(*tail_tmp), &(*storage));
	else if ((*head_tmp)->index < (*head_tmp)->next->index && (*tail_tmp)->index > (*head_tmp)->index)
	{
		if ((*storage)->curr_stack == 'A')
			s_swap(&(*head_tmp), &(*storage), 'a');
		else if ((*storage)->curr_stack == 'B')
			s_swap(&(*head_tmp), &(*storage), 'b');
		r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
	}
	if (is_sorted(*head_tmp) == 1)
		return (1);
	return (-1);
}

int 	sorting_three(t_what **storage)
{
	t_num **head_tmp = NULL;
	t_num **tail_tmp = NULL;

	if ((*storage)->curr_stack == 'A')
	{
		head_tmp = &(*storage)->head_a;
		tail_tmp = &(*storage)->tail_a;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	else if ((*storage)->curr_stack == 'B')
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	return (1);
}

int 	sorting_four(t_what **storage)
{
	while ((*storage)->head_a)
	{
		if ((*storage)->head_a->index == 1 || (*storage)->head_a->index == 4)
		{
			push('b', &(*storage));
			break ;
		}
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	if (sorting_three(&(*storage)) == -1)
		return (-1);
	if ((*storage)->head_b->index == 1)
		push('a', &(*storage));
	else if ((*storage)->head_b->index == 4)
	{
		push('a', &(*storage));
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}

int 	sorting_five(t_what **storage)
{
	push('b', &(*storage));
	push('b', &(*storage));
	if (sorting_three(&(*storage)) == -1)
		return (-1);
	if ((*storage)->head_b->index > (*storage)->tail_b->index)
		s_swap(&(*storage)->head_b, &(*storage), 'b');
	while ((*storage)->stack_b > 0)
	{
		if ((*storage)->head_b->index == (*storage)->head_a->index - 1)
			push('a', &(*storage));
		else if ((*storage)->head_b->index == (*storage)->tail_a->index + 1)
		{
			push('a', &(*storage));
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
		}
		else
			r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	}
	while (is_sorted((*storage)->head_a) == -1)
		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
	if (is_sorted((*storage)->head_a) == 1)
		return (1);
	return (-1);
}