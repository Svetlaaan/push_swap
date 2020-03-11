#include "push_swap.h"

void	free_num(t_num *tmp, t_num *tmp_prev)
{
	while (tmp)
	{
		(tmp_prev) = (tmp)->prev;
		(tmp)->sign = 0;
		(tmp)->num = 0;
		(tmp)->index = 0;
		(tmp)->flag = 0;
		(tmp)->sort = 0;
		(tmp)->flag_st_b = 0;
		if ((tmp)->next)
			(tmp)->next = NULL;
		(tmp)->prev = NULL;
		free(tmp);  // нужно фришить когда push_swap.c
		(tmp) = (tmp_prev);
	}
	free(tmp);
	free(tmp_prev);
}

void 	final_free(t_what **storage, t_num **num)
{
	t_num *tmp = NULL;
	t_num *tmp_prev = NULL;

	if ((*storage)->head_a)
	{
		if ((*storage)->tail_a && (*storage)->tail_a->next && (*storage)->tail_a->next->num == -1)
		{
			(*storage)->tail_a->next->num = 0;
			(*storage)->tail_a->next->index = 0;
			(*storage)->tail_a->next->prev = NULL;
			free((*storage)->tail_a->next);
			(*storage)->tail_a->next = NULL;
		}
		if ((*storage)->tail_a)
			tmp = (*storage)->tail_a;
		else
			tmp = (*storage)->head_a;
		free_num(tmp, tmp_prev);
	}
	if ((*storage)->head_b)
	{
		if ((*storage)->tail_b)
			tmp = (*storage)->tail_b;
		else
			tmp = (*storage)->head_b;
		free_num(tmp, tmp_prev);
	}
	else if ((*storage)->head_a == NULL && (*storage)->head_b == NULL)
	{
		(*num)->num = 0;
		(*num)->sign = 0;
		(*num)->index = 0;
		(*num)->sort = 0;
		(*num)->flag_st_b = 0;
		(*num)->next = NULL;
		(*num)->prev = NULL;
        (*num)->flag = 0;
		free(*num);
	}
	(*storage)->flag_v = 0;
	(*storage)->flag_kol_op = 0;
	(*storage)->stack_a = 0;
	(*storage)->stack_b = 0;
	(*storage)->curr_stack = 0;
	(*storage)->next = 0;
	(*storage)->max = 0;
	(*storage)->mid = 0;
	(*storage)->flag = 0;
	(*storage)->argc = 0;
	free(*storage);
}


t_num		*new_num(void)
{
	t_num *new;

	if (!(new = (t_num *)malloc(sizeof(t_num))))
		return (NULL);
	new->num = -1;
	new->sign = 0;
	new->index = -1;
	new->next = NULL;
	new->prev = NULL;
	new->sort = 0;
	new->flag = 0;
	new->flag_st_b = 0;
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
	storage->curr_stack = 0;
	storage->stack_a = 0;
	storage->stack_b = 0;
	storage->flag_v = 0;
	storage->flag_kol_op = 0;
	storage->max = 0;
	storage->mid = 0;
	storage->next = 1;
	storage->flag = 0;
	storage->argc = 0;
	return (storage);
}

int save_argv(const char *argv, t_num **num, t_what **storage)
{
	t_num *tmp;
	int flag = 0;

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
			if ((*num)->num == -1 && (*num)->sign == 0)
			{
				if (*argv == '-') ////////////
				{
					flag += 1;
					argv += 1;
				}
				if(((*num)->num = ft_atoi(argv)) == -1) ///
				{
					printf("Error\n"); //
					return (-1);
				}
				if (flag == 1) ////////////
					(*num)->num *= -1;
				if ((*num)->num == -1)
					(*num)->sign = 1;
				(*storage)->tail_a = (*num);
				if ((*num)->num < 0)
					flag += 1;
			}
			else
			{
				if (!((*num)->next = new_num()))
					return (-1);
				tmp = *num;
				*num = (*num)->next;
				(*num)->prev = tmp;
				if (*argv == '-') ////////////
				{
					flag += 1;
					argv += 1;
				}
				if(((*num)->num = ft_atoi(argv)) == -1) //// -1 argv
				{
					printf("Error\n"); //
					return (-1);
				}
				if (flag == 1)
					(*num)->num *= -1;
				if ((*num)->num == -1)
					(*num)->sign = 1;
				(*storage)->tail_a = (*num);
				if ((*num)->num < 0)
					flag += 1;
			}
			ft_printf("save num = %d\n", (*num)->num);
			if (flag > 1) //////////////////
				flag = 0;
			argv += (ft_len_of_number_int((*num)->num) + flag); // добавила условие в функцию для чисел > 0
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
			write(1, "Error\n", 6);
			return (-1);
		}
	}
	return(0); ///
}
