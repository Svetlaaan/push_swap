/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 18:18:37 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 16:12:07 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		parse_args(t_what *strg, char *line)
{
	if (line == NULL)
		return (0);
	if (!(ft_strcmp("sa", line)) || !(ft_strcmp("sb", line)) ||
		!(ft_strcmp("ss", line)))
		return (parse_args_if_swap(&line, &(strg)));
	else if (!(ft_strcmp("pa", line)))
		return (push('a', &strg));
	else if (!(ft_strcmp("pb", line)))
		return (push('b', &strg));
	else if (!(ft_strcmp("ra", line)) || !(ft_strcmp("rb", line)) ||
		!(ft_strcmp("rr", line)))
		return (parse_args_if_rotate(&line, &(strg)));
	else if (!(ft_strcmp("rra", line)) || !(ft_strcmp("rrb", line)) ||
		!(ft_strcmp("rrr", line)))
		return (parse_args_if_rev_rotate(&line, &(strg)));
	return (-1);
}

int		valid_and_parse_args(t_what *storage)
{
	int		res;
	char	*line;

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

int		main(int argc, char **argv)
{
	t_num	*new;
	t_what	*storage;
	int		tmp;

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
