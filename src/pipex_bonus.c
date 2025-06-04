/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:06:14 by sscheini          #+#    #+#             */
/*   Updated: 2025/06/04 14:29:36 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
 * Initializes the comands needed for here_doc to be executed.
 * Sets the infile to NULL, since we will be reading from the STDIN.
 * Sets the outfile name specified on the main arguments.
 * @param env The main enviroment pipex structure.
 * @param argv The main arguments.
 * @param envp The main enviroment path.
 * @param path The enviroment path where execve searches for binaries.
 * @return Returns 0 on a succesfull execution, and -1 in case of error.
 * @note If any error occurs, the function name and error type will be display
 * on STDERR. 
 */
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
	return (ft_do_here_doc(env, envp, argv[2]));
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
	env->outfile = argv[env->cmd_count + 2];
	if (access(env->infile, R_OK | F_OK))
		env->infile = NULL;
	ft_split_free(path);
	return (ft_do_pipe(env, envp));
}

/**
 * Pipex bonus works in the same way than the original, adding the following
 * extra functionalities:
 * 
 *	- Manage multiple pipes.
 *	- Accepts << and >> operators, when here\_doc is specified on the main
 *	argument as argv[1]; 
 */
int	main(int argc, char **argv, char **envp)
{
	t_pipex		env;
	char		**path;
	int			i;

	i = -1;
	errno = ENOEXEC;
	env.cmd = NULL;
	if (argc < 2)
		return (ft_forcend(&env, NULL, "Main"));
	env.cmd_count = ft_get_cmd_count(argv);
	if (env.cmd_count < 2)
		return (ft_forcend(&env, NULL, "Main"));
	path = ft_check_path((const char **) envp);
	env.cmd = malloc((env.cmd_count + 1) * sizeof(t_cmd *));
	if (!path || !env.cmd)
		return (ft_forcend(&env, path, "Main"));
	while (++i < env.cmd_count)
		env.cmd[env.cmd_count] = NULL;
	if (!ft_strncmp(argv[1], "here_doc\0", 10))
		return (ft_here_doc(&env, argv, envp, path));
	return (ft_pipe(&env, argv, envp, path));
}
