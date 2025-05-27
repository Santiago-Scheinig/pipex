/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iq_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:45:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 21:18:23 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * Frees every pointer inside 'wrdstr', then it frees 'wrdstr'.
 */
static	void	ft_memfree(char **wrdstr, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(wrdstr[i]);
		i++;
	}
	free(wrdstr);
}

/**
 * Returns the lenght of a word, using 'c' as the end character, ignoring
 * c coincidences inside single and double quotes (if they open and close).
 */
static	int	ft_wrdlen(char const *s, char c)
{
	char	*tmp;
	char	quote;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i] != c && s[i])
	{
		if (s[i] == '\'')
		{
			tmp = ft_strchr(&s[i + 1], '\'');
			quote = '\'';
		}
		if (s[i] == '\"')
		{
			tmp = ft_strchr(&s[i + 1], '\"');
			quote = '\"';
		}
		if (tmp && ++i)
			while (s[i] != quote)
				i++;
		i++;
	}
	return (i);
}

/**
 * Returns the amount of words found in 's' separated with 'c', ignoring
 * c coincidences in single and double quotes (if they open and close).
 */
static	int	ft_wrdcount(char const *s, char c)
{
	char	*tmp;
	int		count;

	count = 0;
	if (c == 0)
		return (1);
	if (s[0] == 0)
		return (0);
	if (s[0] != c)
		count++;
	tmp = ft_iq_strchr(s, c);
	if (tmp != NULL && tmp[1])
		count += ft_wrdcount(&tmp[1], c);
	return (count);
}

/**
 * Returns an ARRAY of CHAR * with every word found in 's'.
 * - The words are divided using 'c'.
 * 
 * @note  ignores c coincidences in single and double quotes 
 * (if they open and close).
 */
char	**ft_iq_split(char const *s, char c)
{
	char	**wrdstr;
	int		w;
	int		i;

	if (!s)
		return (NULL);
	if (s[0] == 0)
		return (ft_calloc(1, sizeof(char *)));
	i = 0;
	w = ft_wrdcount(s, c);
	wrdstr = (char **) malloc((w + 1) * sizeof(char *));
	if (!wrdstr)
		return (NULL);
	while (i < w)
	{
		while (s[0] == c)
			s = ft_iq_strchr(s, c) + 1;
		wrdstr[i] = ft_substr(s, 0, ft_wrdlen(s, c));
		if (!wrdstr[i])
			return (ft_memfree(wrdstr, i), NULL);
		s = ft_iq_strchr(s, c) + 1;
		i++;
	}
	wrdstr[i] = (void *)(0);
	return (wrdstr);
}
