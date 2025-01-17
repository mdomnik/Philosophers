/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomnik <mdomnik@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:55:31 by mdomnik           #+#    #+#             */
/*   Updated: 2024/07/02 16:23:14 by mdomnik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

static int	ft_isspace_philo(int c);

int	ft_atoi_philo(const char *str, long i)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace_philo(str[i]) == 1)
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10;
		result = result + (str[i] - 48);
		i++;
	}
	result = result * sign;
	if (result > INT_MAX || result < INT_MIN || str[i] != '\0' || result < 1)
		error_philo(ERR_NUM);
	return ((int)result);
}

static int	ft_isspace_philo(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
