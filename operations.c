#include "push_swap.h"
#include <stdio.h>

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
			(*storage)->tail_b = (*to);
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
		}

		else if (c == 'b')
		{
			(*storage)->stack_a -= 1;
			(*storage)->stack_b += 1;
			if ((*storage)->stack_a == 0)
				(*storage)->tail_a = NULL;
		}
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
            printf("%7i | %7c\n", tmp_a->num, ' '); ///
            tmp_a = tmp_a->next;
        }
        else if (tmp_a == NULL && tmp_b)
        {
            printf("%7c | %7i\n", ' ', tmp_b->num); ///
            tmp_b = tmp_b->next;
        }
        else if (tmp_a && tmp_b)
        {
            printf("%7i | %7i\n", tmp_a->num, tmp_b->num); ///
            tmp_a = tmp_a->next;
            tmp_b = tmp_b->next;
        }

    }
    printf("%7s | %7s\n", "stack A", "stack B");
}

int s_swap(t_num **head, t_what **storage)
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
		if ((*storage)->stack_a == 2)
			(*storage)->tail_a = (*head)->next;
		else if ((*storage)->stack_b == 2)
			(*storage)->tail_b = (*head)->next;
		(*storage)->flag_kol_op += 1;
	}
	if ((*storage)->flag_v == 1)
		print_stacks((*storage)->head_a, (*storage)->head_b);
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
	return (1);
}