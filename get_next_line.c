/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbauduin <nbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:09:19 by nbauduin          #+#    #+#             */
/*   Updated: 2021/01/14 15:31:26 by nbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!(new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
					* sizeof(char))))
		return (0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		new[j] = s2[i];
		i++;
		j++;
	}
	new[j] = '\0';
	free(s1);
	return (new);
}

char	*ft_keep_rest(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str[i] != '\n')
	{
		i++;
	}
	if (!(result = malloc((ft_strlen(str) - i + 1) * sizeof(char))))
		return (0);
	i++;
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

char	*tmp_for_line(char *tmp)
{
	int		j;
	char	*str;

	j = 0;
	while (tmp[j] != '\n' && tmp[j])
		j++;
	if (!(str = malloc(sizeof(char) * (j + 1))))
		return (0);
	str[j] = '\0';
	j--;
	while (j >= 0)
	{
		str[j] = tmp[j];
		j--;
	}
	return (str);
}

char	*fill_tmp(int fd, char *tmp)
{
	char	*buffer;
	ssize_t	read_result;

	read_result = 1;
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	while (!ft_find_n(tmp) && read_result)
	{
		if ((read_result = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (0);
		buffer[read_result] = '\0';
		if (!(tmp = ft_join(tmp, buffer)))
			return (0);
	}
	free(buffer);
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char	*tmp;

	if (fd == -1 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!tmp)
		if (!(tmp = ft_initialize_tmp()))
			return (-1);
	if (!(tmp = fill_tmp(fd, tmp)))
		return (-1);
	if (!(*line = tmp_for_line(tmp)))
		return (-1);
	if (!ft_find_n(tmp))
	{
		tmp = NULL;
		return (0);
	}
	if (!(tmp = ft_keep_rest(tmp)))
		return (-1);
	return (1);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	*line;
	int		k;
	int		l;

	k = open("test.txt", O_RDONLY);
	l = 1;
	while (get_next_line(k, &line))
	{
		printf("ligne %d : %s\n\n", l, line);
		free(line);
		l++;
	}
	printf("last ligne %d : %s\n\n", l, line);
	free(line);
}
