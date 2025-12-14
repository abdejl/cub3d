/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_get_next_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 10:14:17 by yael-bar          #+#    #+#             */
/*   Updated: 2025/12/14 10:14:29 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	copy_data(char *s1, char *s2, char *r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		r[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		r[j] = s2[i];
		i++;
		j++;
	}
	r[j] = '\0';
}

void	*ft_strjoin(char *s1, char *s2)
{
	char	*r;
	int		size_s1;
	int		size_s2;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	r = malloc(size_s1 + size_s2 + 1);
	if (r == NULL)
		free_all();
	copy_data(s1, s2, r);
	free(s1);
	return (r);
}
