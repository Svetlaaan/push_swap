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

int how_much_sort(t_what **storage)
{
	t_num *tmp;
	int len = 0;

	tmp = (*storage)->curr_stack == 'A' ? (*storage)->head_a : (*storage)->head_b;
	while (tmp)
	{
		if (tmp->sort == 1)
			len += 1;
		tmp = tmp->next;
	}
	return (len);
}

int how_much_nonsort(t_what **storage, int i)
{
	t_num *tmp;
	int len = 0;

	tmp = (*storage)->curr_stack == 'A' ? (*storage)->head_a : (*storage)->head_b;
	while (tmp)
	{
		if (tmp->sort == 0 && tmp->flag_st_b == i)
			len += 1;
		tmp = tmp->next;
	}
	return (len);
}

void    set_block(t_what **storage)
{
	t_num   *tmp;
	int 	mid = 0;
	int 	min = 0;
	int 	max = 0;
	int     i = 0;

	if ((*storage)->curr_stack == 0 || (*storage)->stack_b == 0)
		(*storage)->curr_stack = 'A';
	else if ((*storage)->curr_stack != 0)
		(*storage)->curr_stack = 'B';
	if ((*storage)->curr_stack == 'A' && (*storage)->flag == 0)
	{
		min = find_min(&(*storage)->head_a, &(*storage), i);
		max = find_max(&(*storage)->head_a, &(*storage), i);
		(*storage)->max = max;
		mid = (max / 2) + min;
	}
	else if ((*storage)->curr_stack == 'B')
	{
	    i = (*storage)->head_b->flag_st_b;
		min = find_min(&(*storage)->head_b, &(*storage), i);////
		max = find_max(&(*storage)->head_b, &(*storage), i);
		(*storage)->max = max;
		if ((*storage)->flag > 0)
            mid = (max - min) / 2 + min;
		else
			mid = (max / 2) + min;
        (*storage)->flag += 1;
	}
	else
    {
        i = (*storage)->head_a->flag_st_b;
        min = find_min(&(*storage)->head_a, &(*storage), i);
        max = find_max(&(*storage)->head_a, &(*storage), i);
        (*storage)->max = max;
        mid = (max - min) / 2 + min;
    }
	(tmp) = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
	int count = how_much_nonsort(&(*storage), i);
	if (count <= 5 && (*storage)->curr_stack == 'A')
	{
		while (count--)
        {
		    if (tmp->index == (*storage)->next)
            {
                r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
                (*storage)->tail_a->sort = 1;
                (*storage)->next += 1;
            }
		    else
                push('b', &(*storage));
            (tmp) = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
        }
	}
	else if ((*storage)->stack_b == 0 && (*storage)->flag > 0)
	{
		while (count-- && tmp)
		{
			if ((tmp->flag_st_b == i || tmp->flag_st_b == 0) && tmp->sort == 0)
            {
                if (tmp->index == (*storage)->next)
                {
                    r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
                    (*storage)->tail_a->sort = 1;
                    (*storage)->next += 1;
                }
                else
                    push('b', &(*storage));
            }
            (tmp) = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
		}
	}
	else
	{
		while (count--)
		{
			if ((tmp)->index <= mid && (tmp)->index >= min)
			{
				if ((*storage)->curr_stack == 'A')
					push('b', &(*storage));
				else
                    r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
			}
			else
			{
				if ((*storage)->curr_stack == 'A')
					r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
				else
                {
                    push('a', &(*storage));
                    (*storage)->head_a->flag_st_b = (*storage)->flag;
                    while ((*storage)->head_a->index == (*storage)->next)
                    {
                        r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
                        (*storage)->tail_a->sort = 1;
                        (*storage)->next += 1;
                    }
                }
				/*поменяла местами условия для стэка В -> если меньше mid остается в стэке и сортируется */
			}
			(tmp) = ((*storage)->curr_stack == 'A') ? ((*storage)->head_a) : ((*storage)->head_b);
		}
	}
}

int	push_from_b_if_sort(t_what **storage)
{
	if (is_sorted((*storage)->head_b) == 1)
	{
		while ((*storage)->stack_b > 0)
		{
			push('a', &(*storage));
            (*storage)->head_a->flag_st_b = (*storage)->flag;
            while ((*storage)->head_a->index == (*storage)->next)
			{
				r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
				(*storage)->tail_a->sort = 1;
				(*storage)->next += 1;
			}
		}
		return (1);
	}
	printf("lalalalal");
	return (1); //////////////
}

int 	sorting_al(t_what **storage)
{
    int i = (*storage)->flag;

	if ((*storage)->stack_a <= 5)
	{
		(*storage)->curr_stack = 'A';
		if ((*storage)->stack_a == 5)
			sorting_five(&(*storage));
		else if ((*storage)->stack_a == 4)
			sorting_four(&(*storage));
		else if ((*storage)->stack_a == 3)
			sorting_three(&(*storage));
		else if ((*storage)->stack_a == 2)
			sorting_two(&(*storage));
		if (is_sorted_final((*storage)) == 1)
			return (1);
	}
	while (is_sorted_final(*storage) == -1)
	{
		set_block(&(*storage));
		while ((*storage)->stack_b >= 5)
		{
			if ((*storage)->stack_b == 4)
			{
				int max = find_max(&(*storage)->head_b, &(*storage), i);
				int min = find_min(&(*storage)->head_b, &(*storage), i);
				while ((*storage)->head_b)
				{
					if ((*storage)->head_b->index == min || (*storage)->head_b->index == max)
					{
						push('a', &(*storage));
						break;
					}
					r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
				}
				(*storage)->curr_stack = 'B';
				if (sorting_three(&(*storage)) == -1)
					return (-1);
				if ((*storage)->head_a->index == (*storage)->next)
				{
                    (*storage)->head_a->flag_st_b = (*storage)->flag;
					r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
					(*storage)->tail_a->sort = 1;
					(*storage)->next += 1;
				}
				else
                    (*storage)->head_a->flag_st_b = (*storage)->flag;
				while ((*storage)->stack_b > 0)
				{
					push('a', &(*storage));
                    (*storage)->head_a->flag_st_b = (*storage)->flag;
					if ((*storage)->head_a->index == (*storage)->next)
					{
						r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
						(*storage)->tail_a->sort = 1;
						(*storage)->next += 1;
					}
				}
				while ((*storage)->head_a->index == (*storage)->next)
				{
					r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
					(*storage)->tail_a->sort = 1;
					(*storage)->next += 1;
				}
			}
//            if ((*storage)->stack_b == 5)
//            {
//                push('a', &(*storage));
//                push('a', &(*storage));
//                (*storage)->curr_stack = 'B';
//                if (sorting_three(&(*storage)) == -1)
//                    return (-1);
//                if ((*storage)->head_a->next->index == (*storage)->tail_b->index + 1)
//                        s_swap(&(*storage)->head_a, &(*storage), 'a');
//                while ((*storage)->stack_b < 5)
//                {
//                    if ((*storage)->head_a->next->index == (*storage)->tail_b->index + 1  || (*storage)->head_a->next->index == (*storage)->head_b->index - 1)
//                        s_swap(&(*storage)->head_a, &(*storage), 'a');
//                    if ((*storage)->head_a->index == (*storage)->head_b->index - 1)
//                        push('b', &(*storage));
//                    else if ((*storage)->head_a->index == (*storage)->tail_b->index + 1)
//                    {
//                        push('b', &(*storage));
//                        r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
//                    }
//                    else
//                        r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
//                }
//                while (is_sorted((*storage)->head_b) == -1)
//                    r_rotate(&(*storage)->head_b, &(*storage)->tail_b, &(*storage));
//                (*storage)->flag += 1;
//                while ((*storage)->stack_b > 0)
//                {
//                    push('a', &(*storage));
//                    if ((*storage)->head_a->index == (*storage)->next)
//                    {
//                        r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
//                        (*storage)->tail_a->sort = 1;
//                        (*storage)->next += 1;
//                    }
//                }
//                while ((*storage)->head_a->index == (*storage)->next)
//                {
//                    r_rotate(&(*storage)->head_a, &(*storage)->tail_a, &(*storage));
//                    (*storage)->tail_a->sort = 1;
//                    (*storage)->next += 1;
//                }
//            }
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
            if (push_from_b_if_sort(&(*storage)) == -1)
                return (-1);
		}
	}
	return (0);
}
