/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   provisoire_ok_get_next_line.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbauduin <nbauduin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:09:19 by nbauduin          #+#    #+#             */
/*   Updated: 2020/12/22 11:11:19 by nbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		ft_strlen(char *str)
{
	int n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

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

char	*ft_initialize_tmp(void)
{
	char *str;

	if (!(str = malloc(sizeof(char))))
		return (0);
	*str = '\0';
	return (str);
}

int		fill_line(char **line, char *str, int i)
{
	int	j;

	j = 0;
	while (str[j] != '\n' && str[j])
		j++;
	if (!(line[i] = malloc(sizeof(char) * (j + 1))))
		return (0);
	(line[i])[j] = '\0';
	j--;
	while (j >= 0)
	{
		(line[i])[j] = str[j];
		j--;
	}
	return (1);
}

char	*fill_tmp(int fd, char *tmp)
{
	char	*buffer;
	ssize_t	read_result;

	read_result = 1;
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	buffer[BUFFER_SIZE] = '\0';
	while (!ft_find_n(tmp) && read_result)
	{
		if ((read_result = read(fd, buffer, BUFFER_SIZE)) == -1)
			return (0);
		if (!(tmp = ft_join(tmp, buffer)))
			return (0);
	}
//	printf("buffer %s\n", buffer);
	free(buffer);
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static int	i;
	static char	*tmp;

	if (!i)
		if (!(tmp = ft_initialize_tmp()))
			return (-1);
	if (!(tmp = fill_tmp(fd, tmp)))
		return (-1);
//	printf ("tmp hors fonction %s\n STOP \n", tmp);
	if (!ft_find_n(tmp))
	{
		free(tmp);
		return (0);
	}
	if (!(fill_line(line, tmp, i)))
		return (-1);
	i++;
//	printf("tmp avant keep %d\n", i - 1);
	if (!ft_find_n(tmp))
		return (0);
	if (!(tmp = ft_keep_rest(tmp)))
		return (-1);
//	printf("tmp gardé %d : %s\n", i - 1, tmp);
	return (1);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		main(void)
{
	char	**line;
	int		k;
	int		l;

	line = malloc(8 * sizeof(char*));
	k = open("./test.txt", O_RDONLY);
	l = 0;
	while (get_next_line(k, line))
	{
		printf("ligne %d : %s\n\n", l + 1, line[l]);
		l++;
	}
	l--;
	while (l >= 0)
	{
		free(line[l]);
		l--;
	}
	free(line);
}
