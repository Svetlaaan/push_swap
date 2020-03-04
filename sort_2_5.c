#include "push_swap.h"

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

int 	sorting_two(t_what **storage) ///
{
	if ((*storage)->stack_b == 2)
	{
		if ((*storage)->head_b->index > (*storage)->tail_b->index)
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
	if ((*storage)->head_b->index < (*storage)->tail_b->index && (*storage)->stack_b == 2)
		s_swap(&(*storage)->head_b, &(*storage), 'b');
	if ((*storage)->curr_stack == 'A' && (*storage)->stack_a == 3)
		while ((*storage)->stack_b > 0)
			push('a', &(*storage));
	else if ((*storage)->curr_stack == 'B')
	{
		if ((*storage)->head_a->index < (*storage)->head_a->next->index)
			s_swap(&(*storage)->head_a, &(*storage), 'a');
		while ((*storage)->stack_a > 0 && (*storage)->head_a->podblock == 1)
			push('b', &(*storage));
	}
	print_stacks((*storage)->head_a, (*storage)->head_b);
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
	return (-1);
}

int 	sort_3_mov_rev(t_what **storage, t_num **head_tmp, t_num **tail_tmp)
{
	if (is_sorted_rev((*storage)->head_b) == 1)
		return (1);
	if ((*head_tmp)->index < (*head_tmp)->next->index && (*head_tmp)->index > (*tail_tmp)->index)
		s_swap(&(*head_tmp), &(*storage), 'b');
	else if ((*head_tmp)->index > (*head_tmp)->next->index && (*head_tmp)->index < (*tail_tmp)->index)
		rr_reverse(&(*head_tmp), &(*tail_tmp), &(*storage));
	else if ((*head_tmp)->index < (*head_tmp)->next->index && (*head_tmp)->next->index < (*tail_tmp)->index)
	{
		s_swap(&(*head_tmp), &(*storage), 'b');
		rr_reverse(&(*head_tmp), &(*tail_tmp), &(*storage));
	}
	else if ((*head_tmp)->next->index > (*tail_tmp)->index && (*head_tmp)->next->index > (*head_tmp)->index && (*tail_tmp)->index > (*head_tmp)->index)
		r_rotate(&(*head_tmp), &(*tail_tmp), &(*storage));
	else if((*head_tmp)->index > (*head_tmp)->next->index && (*head_tmp)->next->index < (*tail_tmp)->index)
	{
		rr_reverse(&(*head_tmp), &(*tail_tmp), &(*storage));
		s_swap(&(*head_tmp), &(*storage), 'b');
	}
	if (is_sorted_rev(*head_tmp) == 1)
		return (1);
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
		rr_reverse(&(*head_tmp), &(*storage)->tail_a, &(*storage));
	else if ((*head_tmp)->index < (*head_tmp)->next->index && (*tail_tmp)->index > (*head_tmp)->index)
	{
		if ((*storage)->curr_stack == 'A')
			s_swap(&(*head_tmp), &(*storage), 'a');
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

	if ((*storage)->stack_a == 3)
	{
		head_tmp = &(*storage)->head_a;
		tail_tmp = &(*storage)->tail_a;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	if ((*storage)->stack_b == 3 && is_sorted((*storage)->head_a) == 1)
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		if (sort_3_mov_rev(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	else if (((*storage)->stack_b == 3 && is_sorted((*storage)->head_a) == -1))
	{
		head_tmp = &(*storage)->head_b;
		tail_tmp = &(*storage)->tail_b;
		if (sort_3_mov(&(*storage), &(*head_tmp), &(*tail_tmp)) == -1)
			return (-1);
	}
	/*if ((*storage)->stack_b > 0 && is_sorted((*storage)->head_a) == 1)
	{
		while ((*storage)->stack_b > 0)
		{
			push('a', &(*storage));
		}
	}*/
//	else if ((*storage)->stack_b > 0 && is_sorted((*storage)->head_a) == 1 && is_sorted((*storage)->head_b) == 1)
//	{
//		push('a', &(*storage));
//		r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
//	}
	return (1);
}
