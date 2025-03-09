/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:45:13 by dqaddomi          #+#    #+#             */
/*   Updated: 2024/09/15 12:42:03 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **res, size_t i)
{
	while (i > 0)
		free(res[--i]);
	free(res);
}

static size_t	ft_word_count(char *str, char c)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			w++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (w);
		}
		i++;
	}
	return (w);
}

static size_t	ft_find_start(const char *s, char c, size_t start)
{
	while (s[start] == c)
		start++;
	return (start);
}

static size_t	ft_find_end(const char *s, char c, size_t start)
{
	while (s[start] && s[start] != c)
		start++;
	return (start);
}

char	**ft_split(char const *s, char c)
{
	size_t	start;
	size_t	i;
	char	**res;

	i = 0;
	start = 0;
	if (s == NULL)
		return (NULL);
	res = (char **)malloc((ft_word_count((char *)s, c) + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	while (i < ft_word_count((char *)s, c))
	{
		start = ft_find_start(s, c, start);
		res[i] = ft_substr(s, start, ft_find_end(s, c, start) - start);
		if (!res[i++])
		{
			ft_free(res, i);
			return (NULL);
		}
		start = ft_find_end(s, c, start);
	}
	res[i] = NULL;
	return (res);
}
