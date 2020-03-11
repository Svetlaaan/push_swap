#include "push_swap.h"

int 	new_num_storage(t_num **num, t_what **storage)
{
	if (!((*num) = new_num()))
		return (-1);
	if (!((*storage) = new_what()))
		return (-1);
	return (1);
}

int		sort(t_what **storage)
{
	if (is_sorted(((*storage))->head_a) == -1)
	{
		if (sorting_al(&(*storage)) == -1)
			return (-1);
	}
	if (is_sorted_final((*storage)) == 1)
		ft_printf("\n<3 OK <3\n");
	else
		ft_printf("\n!!! NOOOOO !!!\n");
	print_stacks((*storage)->head_a, (*storage)->head_b);
	return (1);
}

int argv_save(t_what **storage, char **argv, int i, t_num **num)
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

int main(int argc, char **argv) ////
{
    t_num	*num;
    t_what	*storage;
    int		i;

	i = 1;
    if (argc > 1)
	{
		if (new_num_storage(&num, &storage) == -1)
		{
			final_free(&(storage), &(num));
			return (-1);
		}
		storage->argc = argc;
		if (argv_save(&storage, &(*argv), i, &num) == -1)
		{
			final_free(&(storage), &(num));
			return (-1);
		}
		if (index_array(&storage->head_a) == -1 || sort(&storage) == -1)
		{
			final_free(&storage, &num);
			return (-1);
		}
		ft_printf("\nfinal operations: %d\n", storage->flag_kol_op);
		final_free(&storage, &num);
		return (0);
	}
	ft_putstr("Need more arguments!\n");
	return (0);
}

