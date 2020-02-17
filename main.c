#include "push_swap.h"
#include <stdio.h>

void 		final_free(t_num **head)
{

    while (*head)
    {
        (*head)->num = 0;
        (*head)->index = 0;
        (*head)->block = 0;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        (*head) = (*head)->prev;
    }
    free(*head);
}

t_num		*new_num(void)
{
    t_num *new;

    if (!(new = (t_num *)malloc(sizeof(t_num))))
        return (NULL);
    new->num = -1;
    new->index = -1;
    new->block = 0;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

t_what *new_what()
{
    t_what *storage;

    if(!(storage = (t_what*)malloc(sizeof(t_what))))
        return(NULL);
    storage->head_a = NULL;
    storage->head_b = NULL;
    storage->tail_a = NULL;
    storage->tail_b = NULL;
    storage->stack_a = 0;
    storage->stack_b = 0;
    storage->max_index_stack_a = 0;
    storage->min_index_stack_a = 0;
    return (storage);
}

int     check_char(char c)
{
    if ((c >= '0' && c <= '9'))
        return (1);
    return (0);
}

int save_argv(const char *argv, t_num **num, t_what **storage)
{
    t_num *tmp;

    if (argv == NULL || *num == NULL)
        return (-1);
    while (*argv != '\0')
    {
        while (*argv == ' ' || *argv == '\t')
            argv += 1;
        if (check_char(*argv)) //нужна ли проверка на пробелы и тд?
        {
            if ((*storage)->head_a == NULL)
                (*storage)->head_a = *num;
            if ((*num)->num == -1)
            {
                if(((*num)->num = ft_atoi(argv)) == -1) /// выделить память?
                {
                    printf("incorrect number: MIN_INT > || MAX_INT < "); //
                    //final_free(num);
                    return (-1);
                }
            }
            else
                {
                    if (!((*num)->next = new_num()))
                        return (-1);
                    tmp = *num;
                    *num = (*num)->next;
                    (*num)->prev = tmp;
                    if(((*num)->num = ft_atoi(argv)) == -1) /// выделить память?
                    {
                        printf("incorrect number: MIN_INT > || MAX_INT < "); //
                       // final_free(num);
                        return (-1);
                    }
                }
            printf("save num = %d\n", (*num)->num);
            argv += ft_len_of_number(ft_atoi(argv));
            (*storage)->stack_a += 1;
            while (ft_iswhitespace(*argv))
                argv += 1;
            if (*argv == '\0')
            {
                (*storage)->tail_a = *num;
                break ;
            }
        }
        else
            {
                write(1, "Incorrect data\n", 15);
                //final_free(num);
                    return (-1);
            }
    }
    return(0); ///
}

int     index_array(t_num **head)
{
    int     min;
    t_num   *num_min;
    t_num   *tmp;
    int     min_index;
    int 	num_amount;
    int		index;

    min = 0;
    num_min = NULL;
    min_index = -1;
    tmp = *head;
    num_amount = 0;
    index = 1;
    while (tmp)
    {
        num_amount++;
        tmp = tmp->next;
    }
    while (index != num_amount + 1)
    {
        tmp = *head;
        if (tmp->index == -1)
            min = tmp->num;
        else
            {
            while (tmp->index != -1)
                tmp = tmp->next;
            min = tmp->num;
        }
        while (tmp)
        {
            if (tmp->index == -1 && tmp->num <= min)
            {
                min = tmp->num;
                num_min = tmp;
            }
            tmp = tmp->next;
        }
        num_min->index = index;
        index++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_num *num = NULL;
    t_what *storage = NULL;
    int i = 1;

    if (argc < 2)
    {
        ft_putstr("need more arguments!");
        return (0);
    }
    else
        {
        if (!(num = new_num()))
            return (-1);
        if (!(storage = new_what()))
            return (-1);
        while (argc > 1)
        {
            if (save_argv(argv[i], &num, &storage) == -1)
            {
                final_free(&num);
                return (-1);
            }
            argc--;
            i++;
        }
        if ((index_array(&storage->head_a)) == -1)
        {
            final_free(&num);
            return (-1);
        }
    }
    final_free(&num);
    return (0);
}
