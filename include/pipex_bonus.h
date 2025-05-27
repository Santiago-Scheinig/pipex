/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:40:24 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/27 18:04:34 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

/**
 * Executes and pipes every command specified on the program enviroment,
 * but the first command will read from the STDIN instead of the infile 
 * (until the LIMITATOR is writen).
 * @param env The main enviroment pipex structure.
 * @param envp The main enviroment path.
 * @return Returns 0 on a successful execution and -1 in case of error.
 * @note Regardless of the return, it will wait for any child process
 * created during the command executions.
 */
int	ft_do_here_doc(t_pipex *env, char **envp, char *limitator);

#endif