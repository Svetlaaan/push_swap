/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_smthng.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <fboggs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 18:02:17 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 17:17:01 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

int		check_char(char c, const char **av)
{
	if (c == '-')
	{
		if (*(*av - 1) >= '0' && *(*av - 1) <= '9')
			return (0);
		if (*(*av + 1) == '-' || *(*av + 1) == ' ')
			return (0);
	}
	if ((c >= '0' && c <= '9') || (c == '-' && (*(*av + 1) >= '0' &&
		*(*av + 1) <= '9')))
		return (1);
	return (0);
}

int		parse_args_if_swap(char **line, t_what **storage)
{
	if (!(ft_strcmp("sa", *line)))
		return (s_swap(&(*storage)->head_a, &(*storage), 'a'));
	else if (!(ft_strcmp("sb", *line)))
		return (s_swap(&(*storage)->head_b, &(*storage), 'b'));
	else if (!(ft_strcmp("ss", *line)))
	{
		if (s_swap(&(*storage)->head_a, &(*storage), 'a') &&
			s_swap(&(*storage)->head_b, &(*storage), 'b'))
			return (1);
	}
	return (-1);
}

int		parse_args_if_rotate(char **line, t_what **strg)
{
	if (!(ft_strcmp("ra", *line)))
		return (r_rotate(&(*strg)->head_a, &(*strg)->tail_a, &(*strg)));
	else if (!(ft_strcmp("rb", *line)))
		return (r_rotate(&(*strg)->head_b, &(*strg)->tail_b, &(*strg)));
	else if (!(ft_strcmp("rr", *line)))
	{
		if (r_rotate(&(*strg)->head_a, &(*strg)->tail_a, &(*strg))
			&& r_rotate(&(*strg)->head_b, &(*strg)->tail_b, &(*strg)))
			return (1);
	}
	return (-1);
}

int		parse_args_if_rev_rotate(char **line, t_what **strg)
{
	if (!(ft_strcmp("rra", *line)))
		return (rr_reverse(&(*strg)->head_a, &(*strg)->tail_a, &(*strg)));
	else if (!(ft_strcmp("rrb", *line)))
		return (rr_reverse(&(*strg)->head_b, &(*strg)->tail_b, &(*strg)));
	else if (!(ft_strcmp("rrr", *line)))
	{
		if (rr_reverse(&(*strg)->head_a, &(*strg)->tail_a, &(*strg))
			&& rr_reverse(&(*strg)->head_b, &(*strg)->tail_b, &(*strg)))
			return (1);
	}
	return (-1);
}

int		ps_atoi(const char *str, int minus)
{
	size_t				i;
	int					sign;
	long int			res;

	i = 0;
	res = 0;
	sign = minus;
	while (ft_iswhitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (((res > 2147483648) && sign == -1) || (res == 2147483648 &&
			(str[i] - 48) > 8 && sign == -1))
			return (-1);
		else if (res > 2147483647 && sign == 1)
			return (-1);
	}
	return ((int)res);
}
