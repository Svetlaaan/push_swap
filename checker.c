#include "push_swap.h"
#include <stdio.h>

int 	parse_args(t_what *storage, char *line)
{
	if (line == NULL)
		return (0);
	if (!(ft_strcmp("sa", line)))
		return (s_swap(&storage->head_a, &storage));
	else if (!(ft_strcmp("sb", line)))
		return (s_swap(&storage->head_b, &storage));
	else if (!(ft_strcmp("ss", line)))
	{
		if (s_swap(&storage->head_a, &storage) && s_swap(&storage->head_b, &storage))
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
			printf("Error\n");
			return (0);
		}
		ft_putendl(line);
		free(line);
		line = NULL;
	}
	return ((is_sorted_final(storage) == 1) ? 1 : -1);
}

int 	main(int argc, char **argv)
{
	t_num 	*new;
	t_what 	*storage;
	int tmp = 0;
	int i = 1;

	if (argc < 2)
	{
		ft_putstr("\n");
		return (0);
	}
	else
	{
		if (!(new = new_num()))
		{
			final_free(&storage, &new);
			return (-1);
		}
		if (!(storage = new_what()))
		{
			final_free(&storage, &new);
			return (-1);
		}
		while (argc > 1)
		{
			if (storage->flag_v == 0 && (!(ft_strcmp(argv[i], "-v"))))
			{
				storage->flag_v = 1;
				argc--;
				i++;
			}
			if (save_argv(argv[i], &new, &storage) == -1)
			{
				if (storage->head_a)
					final_free(&storage, &new);
				return (-1);
			}
			argc--;
			i++;
		}
		if (index_array(&storage->head_a) == -1)
		{
			final_free(&storage, &new);
			return (-1);
		}
	}
	print_stacks(storage->head_a, storage->head_b);
	if ((tmp = valid_and_parse_args(storage)) == 1)
	{
		print_stacks(storage->head_a, storage->head_b);
		printf("\nfinal operations: %d\n", storage->flag_kol_op);
		printf("OK\n");
	}
	else if (tmp == -1)
	{
		print_stacks(storage->head_a, storage->head_b);
		printf("\nfinal operations: %d\n", storage->flag_kol_op);
		printf("KO\n");
	} ///
	final_free(&storage, &new);
	return (0);
}

/// при запуске теста из сабджекта 3 2 1 0 теряется '3' - DONE - добавлено условие связывания 3 элемента с предыдущим, до этого связь оставалась со старым элементом
/// течет storage - DONE вроде как -> надо еще потестить!