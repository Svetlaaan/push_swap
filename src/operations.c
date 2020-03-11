#include "../inc/push_swap.h"

int		find_min(t_num **stack, int i)
{
	t_num	*tmp;
	t_num	*min;
	int		minimum;

	if (NULL == (*stack))
		return (0);
	tmp = (*stack);
	min = (*stack);
	minimum = (*stack)->index;
	while (tmp)
	{
		if (tmp->index < minimum && tmp->sort == 0 && tmp->flag_st_b == i)
		{
			minimum = tmp->index;
			min = tmp;
		}
		tmp = tmp->next;
	}
	return (min->index);
}

int		find_max(t_num **stack, int i)
{
	t_num	*tmp;
	t_num	*max;
	int		maxi;

	if ((*stack) == NULL)
		return (0);
	tmp = (*stack);
	max = (*stack);
	maxi = (*stack)->index;
	while (tmp)
	{
		if (tmp->index > maxi && tmp->sort == 0 && tmp->flag_st_b == i)
		{
			maxi = tmp->index;
			max = tmp;
		}
		tmp = tmp->next;
	}
	return (max->index);
}

int push(char c, t_what **storage)
{
    t_num **from;
    t_num **to;
    t_num *tmp;
    t_num *tmp_next;

    if (c == 'a')
    {
        from = &(*storage)->head_b;
        to = &(*storage)->head_a;
    }
    else
    {
        from = &(*storage)->head_a;
        to = &(*storage)->head_b;
    }
    if (*from)
	{
		tmp = *from;
		tmp_next = (*from)->next;
		if (*to == NULL)
		{
			*to = *from;
			if (tmp_next)
				tmp_next->prev = NULL;
			(*to)->prev = NULL;
			(*to)->next = NULL;
			*from = tmp_next;
			/*if ((*storage)->stack_b == 1)
				(*storage)->tail_b = (*storage)->head_b;
			if ((*storage)->stack_a == 1)
				(*storage)->tail_a = (*storage)->head_a;*/
		}
		else
		{
			if (tmp_next)
				tmp_next->prev = NULL;
			tmp->prev = NULL;
			tmp->next = *to;
			(*to)->prev = tmp;
			*to = tmp;
			*from = tmp_next;
		}
		if (c == 'a')
		{
			(*storage)->stack_a += 1;
			(*storage)->stack_b -= 1;
			if ((*storage)->stack_b == 0)
				(*storage)->tail_b = NULL;
			ft_printf("pa\n");
		}
		else if (c == 'b')
		{
			(*storage)->stack_a -= 1;
			(*storage)->stack_b += 1;
			if ((*storage)->stack_a == 0)
				(*storage)->tail_a = NULL;
			ft_printf("pb\n");
		}
		if ((*storage)->stack_b == 1)
			(*storage)->tail_b = (*storage)->head_b;
		if ((*storage)->stack_a == 1)
			(*storage)->tail_a = (*storage)->head_a;
		(*storage)->flag_kol_op += 1;
	}
    if ((*storage)->flag_v == 1)
		print_stacks((*storage)->head_a, (*storage)->head_b);
    return (1);
}

void	print_stacks(t_num *head_a, t_num *head_b)
{
    t_num *tmp_a;
    t_num *tmp_b;

    tmp_a = head_a;
    tmp_b = head_b;
    printf("\n"); ///
    while (tmp_a || tmp_b)
    {
        if (tmp_b == NULL && tmp_a)
        {
			ft_printf("%13i | %7c\n", tmp_a->num, ' '); ///
            tmp_a = tmp_a->next;
        }
        else if (tmp_a == NULL && tmp_b)
        {
			ft_printf("%13c | %1i\n", ' ', tmp_b->num); ///
            tmp_b = tmp_b->next;
        }
        else if (tmp_a && tmp_b)
        {
			ft_printf("%13i | %1i\n", tmp_a->num, tmp_b->num); ///
            tmp_a = tmp_a->next;
            tmp_b = tmp_b->next;
        }

    }
	ft_printf("%13s | %7s\n", "stack A", "stack B");
}

int s_swap(t_num **head, t_what **storage, char c)
{
	t_num	*tmp;
	t_num 	*tmp_next;

	if ((*head) && (*head)->next)
	{
		tmp = *head;
		tmp_next = (*head)->next->next;
		*head = (*head)->next;
		(*head)->prev = NULL;
		tmp->next = (*head)->next;
		(*head)->next = tmp;
		tmp->prev = (*head);
		if (tmp_next)
			tmp_next->prev = (*head)->next;
		if ((*storage)->stack_a == 2 && c == 'a')
			(*storage)->tail_a = (*head)->next;
		else if ((*storage)->stack_b == 2 && c == 'b')
			(*storage)->tail_b = (*head)->next;
		(*storage)->flag_kol_op += 1;
	}
	if ((*storage)->flag_v == 1)
		print_stacks((*storage)->head_a, (*storage)->head_b);
	(c == 'a') ? (ft_printf("sa\n")) : (ft_printf("sb\n"));
	return (1);
}

int r_rotate(t_num **head, t_num **tail, t_what **storage)
{
	t_num *tmp;

	tmp = *head;
	if ((*head) && (*head)->next)
	{
		*head = (*head)->next;
		(*head)->prev = NULL;
		(*tail)->next = tmp;
		tmp->prev = *tail;
		tmp->next = NULL;
		*tail = tmp;
		(*storage)->flag_kol_op += 1;
	}
	if ((*storage)->flag_v == 1)
		print_stacks((*storage)->head_a, (*storage)->head_b);
	((*storage)->curr_stack == 'A') ? (ft_printf("ra\n")) : (ft_printf("rb\n"));
	return (1);
}

int rr_reverse(t_num **head, t_num **tail, t_what **storage)
{
	t_num *tmp;

	if ((*head) && (*head)->next)
	{
		tmp = (*tail);

		*tail = (*tail)->prev;
		(*tail)->next = NULL;
		(*head)->prev = tmp;
		tmp->prev = NULL;
		tmp->next = *head;
		*head = tmp;
		(*storage)->flag_kol_op += 1;
	}
	if ((*storage)->flag_v == 1)
		print_stacks((*storage)->head_a, (*storage)->head_b);
	((*storage)->curr_stack == 'A') ? (ft_printf("rra\n")) : (ft_printf("rrb\n"));
	return (1);
}