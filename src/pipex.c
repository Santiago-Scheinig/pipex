/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:40:12 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:36:55 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* char	**ft_get_cmd_args(const char *cmd)//ft_split(cmd, ' ')?
{
	
} */

int		ft_forcend(t_pipex env, char **path, char *ft)
{
	int	i;

	if (env.cmd)
	{
		i = -1;
		while (env.cmd[++i])
		{
			if (env.cmd[i]->args)
				ft_split_free(env.cmd[i]->args);
			if (env.cmd[i]->pathname)
				free(env.cmd[i]->pathname);
			free(env.cmd[i]);
		}
		free(env.cmd);
	}
	if (path)
		ft_split_free(path);
	if (ft)
	{
		perror(ft);
		return (-1);
	}
	return (0);
}

/**
 * 
 * FINISHED
 * 
 */
char	*ft_get_cmd_path(const char *cmd, const char **path)
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
char	**ft_check_path(const char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(&envp[i][5], ':'));
	return (NULL);
}

t_cmd	*ft_new_cmd(const char *cmd, const char **path)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	new->args = ft_split(cmd, ' ');
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

/* int	ft_do_cmd() */

int	ft_do_pipe(t_pipex *env, const char **envp)
{
	//int		pipefd;
	
	env->infile.fd = open(env->infile.name, O_RDONLY);
	if (env->infile.fd < 0)
		return (ft_forcend((*env), NULL, "Ft_do_pipe"));
	dup2(env->infile.fd, STDIN_FILENO);
	execve(env->cmd[0]->pathname, env->cmd[0]->args, (char * const *) envp);
	
/* 	//changes the stdin to fd, so cmd reads from infile instead.
	env->outfile.fd = open(env->infile.name, O_WRONLY);
	dup2(env->outfile.fd, STDOUT_FILENO); //changes the stdout to fd, so cmd writes on outfile instead.
	
	//all the following is looped for each cmd.
	pipe(pipefd);//creates two tmp fd to pipe cmd1 to cmd2 like follow: infile < cmd1 < pipefd[1] | pipefd[0] < cmd2 < outifle;?
	fork(); //creates a child process;
	execve(ft_get_cmd_path, ft_get_cmd_args, envp); //executes the cmd;
	waitpid(0); //waits for child to end. I should wait only for the last one, in case any middle cmd are infinite.
 */	return (0);
} 

int	main(int argc, const char **argv, const char **envp)
{
	t_pipex		env;
	char		**path;
	int			i;

	path = ft_check_path(envp);
	env.cmd_count = 2;
	env.cmd = malloc((env.cmd_count + 1) * sizeof(t_cmd *));
	if (argc != 5 || !path || !env.cmd)
		return (ft_forcend(env, path, "Main"));
	i = -1;
	env.cmd[env.cmd_count] = NULL;
	while (++i < env.cmd_count)
	{
		env.cmd[i] = ft_new_cmd(argv[i + 2], (const char **) path);
		if (!env.cmd[i])
			return (ft_forcend(env, path, "Main"));
		ft_printf("%s\n", env.cmd[i]->pathname);
	}
	env.infile.name = argv[1];
	env.outfile.name = argv[4];
	if (access(env.infile.name, R_OK | F_OK)
		|| access(env.outfile.name, W_OK | F_OK))
		return (ft_forcend(env, path, "Main"));
	ft_split_free(path);
	//ft_do_pipe(&env, envp);
	return (ft_forcend(env, NULL, NULL));
}
