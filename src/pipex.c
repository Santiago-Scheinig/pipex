/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:40:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 18:13:42 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Pipex failsafe, in case of error, frees all memory that could remain
 * allocated in the main structure.
 * @param env The main environment pipex structure.
 * @param path The enviroment path where execve searches for binaries.
 * @param ft_error The function name where the error in question occured.
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
 * Initializes the comands needed for the pipes to be executed.
 * Sets the infile name specified on the main arguments.
 * Sets the outfile name specified on the main arguments.
 * @param env The main enviroment pipex structure.
 * @param argv The main arguments.
 * @param envp The main enviroment path.
 * @param path The enviroment path where execve searches for binaries.
 * @return Returns 0 on a succesfull execution, and -1 in case of error.
 * @note If any error occurs, the function name and error type will be display
 * on STDERR. 
 */
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
 * Pipex is a program that replicates the pipe functionality used in bash.
 * @note This program version allows only two COMMANDS and must specify a
 * preexistent INFILE from where to read, and an OUTFILE where to write the
 * final result; The OUTFILE doesn't necesarely needs to be preexistent. 
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
