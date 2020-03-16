/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 14:51:37 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/16 20:22:42 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		save_av_if_empty(t_what **strg, const char **av, int *flag, t_num **num)
{
	int		minus;

	minus = 1;
	if ((*num)->num == -1 && (*num)->sign == 0)
	{
		if (**av == '-')
		{
			*flag += 1;
			minus *= -1;
			*av += 1;
		}
		if (((*num)->num = ps_atoi(*av, minus)) == -1)
		{
			write(2, "Error\n", 6);
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
	t_num	*tmp;
	int		minus;

	minus = 1;
	if (!((*n)->next = new_num()))
		return (-1);
	tmp = *n;
	*n = (*n)->next;
	(*n)->prev = tmp;
	save_if_minus(av, flag, &minus);
	if (((*n)->num = ps_atoi(*av, minus)) == -1)
	{
		write(2, "Error\n", 6);
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
		if (check_char(**av, av))
		{
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
			write(2, "Error\n", 6);
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
