#include "push_swap.h"
#include <stdio.h>

/*void 		free_num(t_num **head)
{

	while (*head)
	{
		(*head)->num = 0;
		(*head)->index = 0;
		(*head)->block = 0;
		(*head)->next = NULL;
		(*head)->prev = NULL;
		(*head) = (*head)->prev;
		*head = NULL;
	}
	free(*head);

}

void	free_storage(t_what **storage)
{
	(*storage)->head_a = NULL;
	(*storage)->head_b = NULL;
	(*storage)->tail_a = NULL;
	(*storage)->tail_b = NULL;
	(*storage)->stack_a = 0;
	(*storage)->stack_b = 0;
	(*storage)->max_index_stack_a = 0;
	(*storage)->min_index_stack_a = 0;
//		(*storage)->third_step_width = 0;
	free(*storage);
	*storage = NULL;
}*/

void 	final_free(t_what **storage, t_num **num)
{
	t_num *tmp = NULL;
	t_num *tmp_prev = NULL;

	if ((*storage)->head_a)
	{
		tmp = (*storage)->tail_a;
		/*while (tmp)
			tmp = tmp->next;*/
		while (tmp)
		{
			tmp_prev = tmp->prev;
			tmp->num = 0;
			tmp->index = 0;
			tmp->block = 0;
			if (tmp->next)
				tmp->next = NULL;
			tmp->prev = NULL;
			free(tmp);
			tmp = tmp_prev;
		}
		free(tmp);
		free(tmp_prev);
	}
	if ((*storage)->head_b)
	{
		tmp = (*storage)->tail_b;
//		while (tmp)
//			tmp = tmp->next;
		while (tmp->prev)
		{
			tmp_prev = tmp->prev;
			tmp->num = 0;
			tmp->index = 0;
			tmp->block = 0;
			if (tmp->next)
				tmp->next = NULL;
			tmp->prev = NULL;
			free(tmp);
			tmp = tmp_prev;
		}
	}
	/*storage->head_a = NULL;
	storage->head_b = NULL;
	storage->tail_a = NULL;
	storage->tail_b = NULL;*/
	(*storage)->stack_a = 0;
	(*storage)->stack_b = 0;
	(*storage)->max_index_stack_a = 0;
	(*storage)->min_index_stack_a = 0;
	//free(&storage);
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
			if ((*num)->num == -1)
			{
				if(((*num)->num = ft_atoi(argv)) == -1) /// выделить память?
				{
					printf("incorrect number: MIN_INT > || MAX_INT < "); //
					return (-1);
				}
				if ((*num)->num < 0)
					flag = 1;
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
					return (-1);
				}
				if ((*num)->num < 0)
					flag = 1;
			}
			printf("save num = %d\n", (*num)->num);
			argv += (ft_len_of_number((*num)->num) + flag); // добавила условие в функцию для чисел > 0
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
