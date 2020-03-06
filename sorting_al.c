#include "push_swap.h"

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

/*int len_of_block(t_what **storage, int num)
{
	t_num *tmp;
	int len = 0;

	tmp = (*storage)->head_a;
	while (tmp)
	{
		if (tmp->flag == num)
			len += 1;
		tmp = tmp->next;
	}
	tmp = (*storage)->head_b;
	while (tmp)
	{
//		if (tmp->block == num)
			len += 1;
		tmp = tmp->next;
	}
	return (len);
}*/

void    set_block(t_what **storage)
{
	int     num_block;
	t_num   *tmp;
	int mid = 0;
	int min = 0;
	int max = 0;

	if ((*storage)->curr_stack == 0 || (*storage)->stack_b == 0)
		(*storage)->curr_stack = 'A';
	else if ((*storage)->curr_stack != 0)
		(*storage)->curr_stack = 'B';
	if ((*storage)->curr_stack == 'A')
	{
		min = find_min(&(*storage)->head_a, &(*storage));
		(*storage)->next = min;
		max = find_max(&(*storage)->head_a, &(*storage));
		(*storage)->max = max;
		if ((*storage)->flag > 0)
			mid = (max - min)/2 + min;
		else
			mid = (max / 2) + min;
	}
	else if ((*storage)->curr_stack == 'B')
	{
		min = find_min(&(*storage)->head_b, &(*storage));
		(*storage)->next = min;
		max = find_max(&(*storage)->head_b, &(*storage));
		(*storage)->max = max;
		if ((*storage)->flag > 0)
			mid = (max - min)/2 + min;
		else
			mid = (max / 2) + min;
	}
	//num_block = (((*storage)->curr_stack == 'A') ? (*storage)->stack_a / 2 : (*storage)->stack_b / 2); // по сколько элементов в блоке?
	tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
	int count = ((*storage)->curr_stack == 'A') ? (*storage)->stack_a : (*storage)->stack_b;
	while (count--) //&& tmp->flag_st_b <= (*storage)->flag)
	{
		if (tmp->index <= mid && tmp->index >= min) // 1 && tmp->index < 1 + num_block)
		{
			if ((*storage)->curr_stack == 'A')
			{
				push('b', &(*storage));
				(*storage)->head_b->flag_st_b += 1;
			}
			else
			{
				r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
				(*storage)->tail_b->flag_st_b += 1;
			}
		}
		/*else if (tmp->index < min)
			break ;*/
		else
		{
			if ((*storage)->curr_stack == 'A')
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
			else
				push('a', &(*storage));
		}
		tmp = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
	}
}

int	push_from_b_if_sort(t_what **storage)
{
	if (is_sorted((*storage)->head_b) == 1)
	{
		(*storage)->flag += 1;
		while ((*storage)->stack_b > 0)
		{
			push('a', &(*storage));
			if ((*storage)->head_a->index == (*storage)->next)
			{
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
				(*storage)->tail_a->sort = 1;
				(*storage)->next += 1;
			}
		}
		return (1);
	}
	/*else
		return (-1);*/
	printf("lalalalal");
	return (1); //////////////
}

int 	sorting_al(t_what **storage)
{
	if ((*storage)->stack_a <= 5)
	{
		(*storage)->curr_stack = 'A';
		if ((*storage)->stack_a == 5) // no
			sorting_five(&(*storage));
		else if ((*storage)->stack_a == 4)
			sorting_four(&(*storage));
		else if ((*storage)->stack_a == 3)
			sorting_three(&(*storage));
		else if ((*storage)->stack_a == 2)
			sorting_two(&(*storage));
	}
	while (is_sorted_final(*storage) == -1)
	{
		set_block(&(*storage));
		while ((*storage)->stack_b >= 4)
		{
			if ((*storage)->stack_b == 4)
			{
				while ((*storage)->head_b->index > (*storage)->next)
					r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
				push('a', &(*storage));
				if ((*storage)->head_a->index == (*storage)->next)
				{
					r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
					(*storage)->tail_a->sort = 1;
					(*storage)->next += 1;
					break ;
				}
			}
			set_block(&(*storage));
		}
		if ((*storage)->stack_b  == 3)
		{
			(*storage)->curr_stack = 'B';
			sorting_three(&(*storage));
			if (push_from_b_if_sort(&(*storage)) == -1)
				return (-1);
		}
		else if ((*storage)->stack_b == 2)
		{
			sorting_two(&(*storage));
			if (push_from_b_if_sort(&(*storage)) == -1)
				return (-1);
		}
		else if ((*storage)->stack_b == 1)
		{
			push('a', &(*storage));
			if ((*storage)->head_a->index == (*storage)->next)
			{
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
				(*storage)->tail_a->sort = 1;
				(*storage)->next += 1;
			}
		}
	}
	return (0);
}