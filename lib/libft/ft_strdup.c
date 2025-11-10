/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-bar <yael-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:30:10 by abjellal          #+#    #+#             */
/*   Updated: 2025/11/10 15:12:21 by yael-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
		return (NULL);
	j = 0;
	while (s[j])
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*int main()
{
	char str[] = "Hello";
	char *ptr = ft_strdup(str);
	printf("%s", ptr);
}*/
