/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rturcey <rturcey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:57:41 by user42            #+#    #+#             */
/*   Updated: 2020/11/25 15:02:28 by rturcey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*cpy;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	if (!(cpy = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_strjoin_sp(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (s2[j])
		j++;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + j + 2))))
		return (NULL);
	while (s1[++i])
		new[i] = s1[i];
	j = 0;
	new[i++] = ' ';
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s1);
	free(s2);
	return (new);
}
