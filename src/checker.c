/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 18:18:37 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/13 19:34:36 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int 	parse_args(t_what *storage, char *line)
{
	if (line == NULL)
		return (0);
	if (!(ft_strcmp("sa", line)))
		return (s_swap(&storage->head_a, &storage, 'a'));
	else if (!(ft_strcmp("sb", line)))
		return (s_swap(&storage->head_b, &storage, 'b'));
	else if (!(ft_strcmp("ss", line)))
	{
		if (s_swap(&storage->head_a, &storage, 'a') && s_swap(&storage->head_b, &storage, 'b'))
			return (1);
	}
	else if (!(ft_strcmp("pa", line)))
		return (push('a', &storage));
	else if (!(ft_strcmp("pb", line)))
		return (push('b', &storage));
	else if (!(ft_strcmp("ra", line)))
		return (r_rotate(&storage->head_a, &storage->tail_a, &storage));
	else if (!(ft_strcmp("rb", line)))
		return (r_rotate(&storage->head_b, &storage->tail_b, &storage));
	else if (!(ft_strcmp("rr", line)))
	{
		if (r_rotate(&storage->head_a, &storage->tail_a, &storage)
			&& r_rotate(&storage->head_b, &storage->tail_b, &storage))
			return (1);
	}
	else if (!(ft_strcmp("rra", line)))
		return (rr_reverse(&storage->head_a, &storage->tail_a, &storage));
	else if (!(ft_strcmp("rrb", line)))
		return (rr_reverse(&storage->head_b, &storage->tail_b, &storage));
	else if (!(ft_strcmp("rrr", line)))
	{
		if (rr_reverse(&storage->head_a, &storage->tail_a, &storage)
			&& rr_reverse(&storage->head_b, &storage->tail_b, &storage))
			return (1);
	}
	else
		return (-1);
	return (1);
}

int 	valid_and_parse_args(t_what *storage)
{
	int 	res;
	char 	*line;

	while ((res = get_next_line(0, &line)) > 0)
	{
		if (*line == '\0')
		{
			free(line);
			break ;
		}
		if (parse_args(storage, line) == -1)
		{
			free(line);
			ft_printf("Error\n");
			return (0);
		}
		ft_putendl(line);
		free(line);
		line = NULL;
	}
	return ((is_sorted_final(storage) == 1) ? 1 : -1);
}

int		argv_save_checker(t_what **storage, char **argv, int i, t_num **new)
{
	while ((*storage)->argc > 1)
	{
		if ((*storage)->flag_v == 0 && (!(ft_strcmp(argv[i], "-v"))))
		{
			(*storage)->flag_v = 1;
			(*storage)->argc -= 1;
			i++;
			if ((*storage)->argc < 2)
			{
				final_free(&(*storage), &(*new));
				return (-1);
			}
		}
		if (save_argv(argv[i], &(*new), &(*storage)) == -1)
			return (-1);
		(*storage)->argc -= 1;
		i++;
	}
	return (1);
}

int		main_alg_checker(t_what **storage, t_num **num, int argc, char **argv)
{
	int i;

	i = 1;
	if (new_num_storage(&(*num), &(*storage)) == -1)
	{
		final_free(&(*storage), &(*num));
		return (-1);
	}
	(*storage)->argc = argc;
	if (argv_save_checker(&(*storage), &(*argv), i, &(*num)) == -1)
	{
		final_free(&(*storage), &(*num));
		return (-1);
	}
	if (index_array(&(*storage)->head_a) == -1)
	{
		final_free(&(*storage), &(*num));
		return (-1);
	}
	return (1);
}

int 	main(int argc, char **argv)
{
	t_num 	*new;
	t_what 	*storage;
	int tmp;

	tmp = 0;
	if (argc < 2)
		return (0);
	else
	{
		if (main_alg_checker(&(storage), &(new), argc, argv) == -1)
			return (-1);
	}
	if ((tmp = valid_and_parse_args(storage)) == 1)
		ft_printf("OK\n");
	else if (tmp == -1)
		ft_printf("KO\n");
	final_free(&storage, &new);
	return (0);
}

//ft_printf("\nfinal operations: %d\n", storage->flag_kol_op);