/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:06:17 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 21:07:27 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * 
 * FINISHED
 * 
 */
char	**ft_check_path(const char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(&envp[i][5], ':'));
	return (NULL);
}

/**
 * 
 * FINISHED
 * 
 */
static char	*ft_get_cmd_path(const char *cmd, const char **path)
{
	char	*cmd_pathname;
	char	*tmp;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_pathname = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(cmd_pathname, X_OK))
			return (cmd_pathname);
		free(cmd_pathname);
	}
	return (NULL);
}

/**
 * 
 * FINISHED
 * 
 */
t_cmd	*ft_new_cmd(const char *cmd, const char **path)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->args = ft_iq_split(cmd, ' ');
	if (!new->args)
		return (NULL);
	new->pathname = ft_get_cmd_path(new->args[0], path);
	if (!new->pathname)
	{
		ft_split_free(new->args);
		free(new);
		return (NULL);
	}
	return (new);
}
