/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:31:34 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/13 19:57:30 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		sort(t_what **storage)
{
	(*storage)->push_swap = 1;
	if (is_sorted(((*storage))->head_a) == -1)
	{
		if (sorting_al(&(*storage)) == -1)
			return (-1);
	}
	return (1);
}

int		argv_save(t_what **storage, char **argv, int i, t_num **num)
{
	while ((*storage)->argc > 1)
	{
		if (save_argv(argv[i], &(*num), &(*storage)) == -1)
			return (-1);
		(*storage)->argc -= 1;
		i++;
	}
	return (1);
}

int		main_alg(t_what **storage, t_num **num, int argc, char **argv)
{
	int i;

	i = 1;
	if (argc > 1)
	{
		if (new_num_storage(&(*num), &(*storage)) == -1)
		{
			final_free(&(*storage), &(*num));
			return (-1);
		}
		(*storage)->argc = argc;
		if (argv_save(&(*storage), &(*argv), i, &(*num)) == -1)
		{
			final_free(&(*storage), &(*num));
			return (-1);
		}
		if (index_array(&(*storage)->head_a) == -1 || sort(&(*storage)) == -1)
		{
			final_free(&(*storage), &(*num));
			return (-1);
		}
		ft_printf("\nOK");
		final_free(&(*storage), &(*num));
		return (1);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_num	*num;
	t_what	*storage;

	if (argc > 1)
	{
		if (main_alg(&(storage), &num, argc, &(*argv)) == -1)
			return (-1);
		return (0);
	}
	ft_putstr("Need more arguments!\n");
	return (0);
}
