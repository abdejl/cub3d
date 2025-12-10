/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 15:13:35 by abjellal          #+#    #+#             */
/*   Updated: 2025/12/10 21:48:18 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 1);
	if (!str)
		free_all();
	add_m_node(str);
	j = 0;
	while (s[j])
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}