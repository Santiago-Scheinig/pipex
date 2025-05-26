/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:40:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 21:08:37 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * 
 * FINISHED
 * 
 */
int	ft_forcend(t_pipex *env, char **path, char *ft_error)
{
	int	i;

	if (env->cmd)
	{
		i = -1;
		while (env->cmd[++i])
		{
			if (env->cmd[i]->args)
				ft_split_free(env->cmd[i]->args);
			if (env->cmd[i]->pathname)
				free(env->cmd[i]->pathname);
			free(env->cmd[i]);
		}
		free(env->cmd);
	}
	if (path)
		ft_split_free(path);
	if (ft_error)
	{
		perror(ft_error);
		return (-1);
	}
	return (0);
}

static int	ft_pipe(t_pipex *env, char **argv, char **envp, char **path)
{
	int	i;

	i = -1;
	while (++i < env->cmd_count)
	{
		env->cmd[i] = ft_new_cmd(argv[i + 2], (const char **) path);
		if (!env->cmd[i])
			return (ft_forcend(env, path, "Ft_new_cmd"));
	}
	env->infile = argv[1];
	env->outfile = argv[4];
	if (access(env->infile, R_OK | F_OK))
		return (ft_forcend(env, path, "Access"));
	ft_split_free(path);
	return (ft_do_pipe(env, envp));
}

/**
 * 
 * FINISHED
 * 
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex		env;
	char		**path;

	errno = ENOEXEC;
	path = ft_check_path((const char **) envp);
	env.cmd_count = 2;
	env.cmd = malloc((env.cmd_count + 1) * sizeof(t_cmd *));
	if (argc != 5 || !path || !env.cmd)
		return (ft_forcend(&env, path, "Main"));
	env.cmd[env.cmd_count] = NULL;
	return (ft_pipe(&env, argv, envp, path));
}
