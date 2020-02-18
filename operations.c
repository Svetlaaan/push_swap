#include "push_swap.h"
#include <stdio.h>

int r_rotate(t_num **head, t_num **tail)
{
    t_num *tmp;

    tmp = *head;
    if (!(*head)->next) // ?
        return (1);
    *head = (*head)->next;
    (*head)->prev = NULL;
    (*tail)->next = tmp;
    tmp->prev = *tail;
    tmp->next = NULL;
    *tail = tmp;
    return (1);
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
        if ((*storage)->tail_b == NULL)
            (*storage)->tail_b = (*storage)->head_a;
    }
    if (*from == NULL)
        return (-1);
    tmp = *from;
    tmp_next = (*from)->next;
    if (*to == NULL)
    {
        *to = *from;
        tmp_next->prev = NULL;
        (*to)->prev = NULL;
        (*to)->next = NULL;
        *from = tmp_next;
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
    return (1);
}

void	print_stacks(t_num *head_a, t_num *head_b)
{
    t_num *tmp_a;
    t_num *tmp_b;

    tmp_a = head_a;
    tmp_b = head_b;
    printf("\n");
    while (tmp_a || tmp_b)
    {
        if (tmp_b == NULL && tmp_a)
        {
            printf("%7i | %7c\n", tmp_a->num, ' ');
            tmp_a = tmp_a->next;
        }
        else if (tmp_a == NULL && tmp_b)
        {
            printf("%7c | %7i\n", ' ', tmp_b->num);
            tmp_b = tmp_b->next;
        }
        else if (tmp_a && tmp_b)
        {
            printf("%7i | %7i\n", tmp_a->num, tmp_b->num);
            tmp_a = tmp_a->next;
            tmp_b = tmp_b->next;
        }

    }
    printf("%7s | %7s\n", "stack A", "stack B");
}