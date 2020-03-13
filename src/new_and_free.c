/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:16:14 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/13 18:56:51 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

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
		free(tmp);
		(tmp) = (tmp_prev);
	}
	free(tmp);
	free(tmp_prev);
}

void	free_stack_a(t_what **storage)
{
	t_num *tmp;
	t_num *tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	if ((*storage)->head_a)
	{
		if ((*storage)->tail_a && (*storage)->tail_a->next &&
		(*storage)->tail_a->next->num == -1)
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
}

void	free_stack_b(t_what **storage)
{
	t_num *tmp;
	t_num *tmp_prev;

	tmp = NULL;
	tmp_prev = NULL;
	if ((*storage)->head_b)
	{
		if ((*storage)->tail_b)
			tmp = (*storage)->tail_b;
		else
			tmp = (*storage)->head_b;
		free_num(tmp, tmp_prev);
	}
}

void	final_free(t_what **storage, t_num **num)
{
	if ((*storage)->head_a)
		free_stack_a(&(*storage));
	if ((*storage)->head_b)
		free_stack_b(&(*storage));
	else if ((*storage)->head_a == NULL && (*storage)->head_b == NULL)
		free(*num);
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

t_num	*new_num(void)
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

t_what	*new_what(void)
{
	t_what *storage;

	if (!(storage = (t_what*)malloc(sizeof(t_what))))
		return (NULL);
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
	storage->push_swap = 0;
	return (storage);
}

int		save_av_if_empty(t_what **strg, const char **av, int *flag, t_num **num)
{
	if ((*num)->num == -1 && (*num)->sign == 0)
	{
		if (**av == '-')
		{
			*flag += 1;
			*av += 1;
		}
		if (((*num)->num = ft_atoi(*av)) == -1)
		{
			ft_printf("Error\n");
			return (-1);
		}
		if ((*flag) == 1)
			(*num)->num *= -1;
		if ((*num)->num == -1)
			(*num)->sign = 1;
		(*strg)->tail_a = (*num);
		if ((*num)->num < 0)
			*flag += 1;
	}
	return (1);
}

int		save_if_not_empty(t_num **n, const char **av, int *flag, t_what **strg)
{
	t_num *tmp;

	if (!((*n)->next = new_num()))
		return (-1);
	tmp = *n;
	*n = (*n)->next;
	(*n)->prev = tmp;
	if (**av == '-')
	{
		*flag += 1;
		*av += 1;
	}
	if (((*n)->num = ft_atoi(*av)) == -1)
	{
		ft_printf("Error\n");
		return (-1);
	}
	if (*flag == 1)
		(*n)->num *= -1;
	if ((*n)->num == -1)
		(*n)->sign = 1;
	(*strg)->tail_a = (*n);
	if ((*n)->num < 0)
		*flag += 1;
	return (1);
}

int		save_correct_av(t_what **strg, t_num **num, const char **av, int flag)
{
	if ((*strg)->head_a == NULL)
		(*strg)->head_a = *num;
	if ((*num)->num == -1 && (*num)->sign == 0)
	{
		if (save_av_if_empty(&(*strg), (&(*av)), &flag, &(*num)) == -1)
			return (-1);
	}
	else
	{
		if (save_if_not_empty(&(*num), (&(*av)), &flag, &(*strg)) == -1)
			return (-1);
	}
	if (flag > 1)
		flag = 0;
	(*av) += (ft_len_of_number_int((*num)->num) + flag);
	(*strg)->stack_a += 1;
	while (ft_iswhitespace(**av))
		(*av) += 1;
	return (1);
}

int		what_do_to_save_av(t_what **strg, t_num **n, const char **av, int flag)
{
	while (*av != '\0')
	{
		while (ft_iswhitespace(**av))
			*av += 1;
		if (check_char(**av, n))
		{
			if (**av == '-' && *(*av + 1) == '-')
			{
				write(1, "Error\n", 6);
				return (-1);
			}
			if (save_correct_av(&(*strg), &(*n), &(*av), flag) == -1)
				return (-1);
			if (**av == '\0')
			{
				(*strg)->tail_a = *n;
				break ;
			}
		}
		else
		{
			write(1, "Error\n", 6);
			return (-1);
		}
	}
	return (1);
}

int		save_argv(const char *argv, t_num **num, t_what **storage)
{
	int		flag;

	flag = 0;
	if (argv == NULL || *num == NULL)
		return (-1);
	if (what_do_to_save_av(&(*storage), &(*num), &argv, flag) == -1)
		return (-1);
	return (1);
}

int		new_num_storage(t_num **num, t_what **storage)
{
	if (!((*num) = new_num()))
		return (-1);
	if (!((*storage) = new_what()))
		return (-1);
	return (1);
}
