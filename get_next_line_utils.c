/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:52:44 by nbauduin          #+#    #+#             */
/*   Updated: 2021/01/11 15:52:47 by nbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *str)
{
	int n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

int		ft_find_n(char *tmp)
{
	int n;

	n = 0;
	while (tmp[n])
	{
		if (tmp[n] == '\n')
			return (1);
		n++;
	}
	return (0);
}

char	*ft_initialize_tmp(void)
{
	char *str;

	if (!(str = malloc(sizeof(char))))
		return (0);
	*str = '\0';
	return (str);
}
