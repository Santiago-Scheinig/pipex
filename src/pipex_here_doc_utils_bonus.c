/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:38:00 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 16:54:01 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

/**
 * 
 * FINISHED
 * 
 */
static int	ft_waitfor_childs(t_pipex *env, int exit_status)
{
	int	i;

	i = -1;
	while (++i < env->cmd_count)
		if (env->waitpid_list[i] > 0)
			if (waitpid(env->waitpid_list[i], NULL, 0) == -1)
				return (ft_forcend(env, NULL, "Waitpid"));
	free(env->waitpid_list);
	if (exit_status == EXIT_FAILURE)
		return (ft_forcend(env, NULL, "Pipe"));
	return (ft_forcend(env, NULL, NULL));
}

/**
 * 
 * FINISHED
 * 
 */
static int	ft_do_fork(t_pipex *env, int infd, int pipefd[2], char **envp)
{
	static int	i;

	env->waitpid_list[i] = fork();
	if (!env->waitpid_list[i])
	{
		if (dup2(infd, STDIN_FILENO) == -1
			|| dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("Dup2");
			exit(-1);
		}
		close(infd);
		close(pipefd[0]);
		close(pipefd[1]);
		if (execve(env->cmd[i]->pathname, env->cmd[i]->args, envp) == -1)
		{
			perror("Execve");
			exit(-1);
		}
	}
	i++;
	close(infd);
	close(pipefd[1]);
	return (pipefd[0]);
}

static int	ft_read_to_limitator(char *limitator)
{
	char	*line;
	int		pipefd[2];
	int		limitator_len;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		limitator_len = ft_strlen(limitator);
		if (!ft_strncmp(line, limitator, limitator_len))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	get_next_line(-1);
	return (pipefd[0]);
}

/**
 * 
 * FINISHED
 * 
 */
int	ft_do_here_doc(t_pipex *env, char **envp, char *limitator)
{
	int	i;
	int	infd;
	int	pipefd[2];

	i = -1;
	env->waitpid_list = ft_calloc((env->cmd_count), sizeof(pid_t));
	if (!env->waitpid_list)
		return (-1);
	while (++i < env->cmd_count)
	{
		if (!i && !env->infile)
			infd = ft_read_to_limitator(limitator);
		if (infd < 0 || pipe(pipefd) == -1)
			return (ft_waitfor_childs(env, EXIT_FAILURE));
		if (i == env->cmd_count - 1)
		{
			close(pipefd[1]);
			pipefd[1] = open(env->outfile, O_CREAT | O_APPEND | O_WRONLY, 420);
			if (pipefd[1] < 0)
				return (ft_waitfor_childs(env, EXIT_FAILURE));
		}
		infd = ft_do_fork(env, infd, pipefd, envp);
	}
	return (ft_waitfor_childs(env, EXIT_SUCCESS));
}
