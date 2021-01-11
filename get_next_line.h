/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbauduin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:51:27 by nbauduin          #+#    #+#             */
/*   Updated: 2021/01/11 15:52:31 by nbauduin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_strlen(char *str);
int		ft_find_n(char *tmp);
char	*ft_initialize_tmp(void);
char	*ft_join(char *s1, char *s2);
char	*ft_keep_rest(char *str);
int		fill_line(char **line, char *str, int i);
char	*fill_tmp(int fd, char *tmp);
int		get_next_line(int fd, char **line);

#endif
