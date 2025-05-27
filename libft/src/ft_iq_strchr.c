/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iq_strchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:15:28 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 21:18:27 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Returns a CHAR * to the first ocurrance of 'c' inside 's'.
 * - Return NULL in case no ocurrance is found.
 * 
 * @note ignores c coincidences in single and double quotes 
 * (if they open and close).
 */
char	*ft_iq_strchr(char const *s, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\'' && s[i + 1])
			tmp = ft_strchr(&s[i + 1], '\'');
		if (s[i] == '\"' && s[i + 1])
			tmp = ft_strchr(&s[i + 1], '\"');
		if (tmp)
		{
			s = tmp;
			i = 0;
			tmp = NULL;
		}
		i++;
	}
	if (!s[i])
		return (NULL);
	return ((char *) &s[i]);
}
