/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:35:34 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/19 17:36:29 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

typedef struct s_file
{
	const char	*name;
	int			fd;
}	t_file;

typedef struct s_cmd
{
	char	**args;
	char	*pathname;
}	t_cmd;

typedef struct s_pipex
{
	t_file	infile;
	t_file	outfile;
	t_cmd	**cmd;
	int		cmd_count;
}	t_pipex;

#endif
