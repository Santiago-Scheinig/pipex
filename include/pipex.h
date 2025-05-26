/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:35:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/26 20:59:57 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/include/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*pathname;
}	t_cmd;

typedef struct s_pipex
{
	const char	*infile;
	const char	*outfile;
	t_cmd		**cmd;
	pid_t		*waitpid_list;
	int			cmd_count;
}	t_pipex;

int		ft_forcend(t_pipex *env, char **path, char *ft_error);

int		ft_do_pipe(t_pipex *env, char **envp);

char	**ft_check_path(const char **envp);

t_cmd	*ft_new_cmd(const char *cmd, const char **path);

#endif
