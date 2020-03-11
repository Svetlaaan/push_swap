#include "../inc/push_swap.h"

int index_array(t_num **head)
{
	int     min;
	t_num   *num_min;
	t_num   *tmp;
	int 	num_amount;
	int		index;
	int 	tmp_min = 100; ///// если оставить -1 то ломается проверка на дубли с -1 -1 НАДО ЧТО-ТО ДЕЛАТЬ!!!!!!!!!!!!!!

	min = 0;
	num_min = NULL;
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
		if (min == tmp_min) //////
		{
			ft_printf("Error\n");
			return (-1);
		}
		num_min->index = index;
		//ft_printf("save num = %d  index = %d\n", num_min->num, num_min->index);
		index++;
		tmp_min = num_min->num;
	}
	return (1);
}