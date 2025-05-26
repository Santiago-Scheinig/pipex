/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:06:14 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 21:07:15 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

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

/**
 * 
 * FINISHED
 * 
 */
static int	ft_get_cmd_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (!ft_strncmp(argv[1], "here\\_doc\0", 10))
		return (i - 4);
	return (i - 3);
}

static int	ft_here_doc(t_pipex *env, char **argv, char **envp, char **path)
{
	int	i;

	i = -1;
	while (++i < env->cmd_count)
	{
		env->cmd[i] = ft_new_cmd(argv[i + 3], (const char **) path);
		if (!env->cmd[i])
			return (ft_forcend(env, path, "Ft_new_cmd"));
	}
	env->infile = NULL;
	env->outfile = argv[env->cmd_count + 3];
	ft_split_free(path);
	return (ft_do_pipe(env, envp));
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
	env->outfile = argv[env->cmd_count + 2];
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
	env.cmd_count = ft_get_cmd_count(argv);
	env.cmd = malloc((env.cmd_count + 1) * sizeof(t_cmd *));
	if (argc < 5 || !path || !env.cmd)
		return (ft_forcend(&env, path, "Main"));
	env.cmd[env.cmd_count] = NULL;
	if (!ft_strncmp(argv[1], "here\\_doc\0", 10))
		return (ft_here_doc(&env, argv, envp, path));
	return (ft_pipe(&env, argv, envp, path));
}
