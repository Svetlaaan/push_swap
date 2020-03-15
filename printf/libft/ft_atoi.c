/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboggs <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:45:22 by fboggs            #+#    #+#             */
/*   Updated: 2020/03/15 16:42:11 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	size_t				i;
	int					sign;
	long int			res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
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
	return ((int)res * sign);
}
