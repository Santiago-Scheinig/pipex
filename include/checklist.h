/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checklist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscheini <sscheini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:08:42 by sscheini          #+#    #+#             */
/*   Updated: 2025/05/24 16:45:00 by sscheini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * int access(const char *pathname, int mode)
 * 
 * Allows to verify if a certain permission is allowed to the pathname file.
 * 
 * R_OK = Read;
 * W_OK = Write;
 * X_OK = Execute;
 * F_OK = File exists;
 * 
 * returns 0 if true, -1 if false;
 */

/**
 * int dup2(int oldfd, int newfd)
 * 
 * Makes newfd to be equal to the oldfd. Making, for example, to stdin read from the oldfd 
 * instead of the fd = 0;
 * 
 * returns newfd;
 */

 /**
  * int pipe(int pipefd[2])
  *
  * Creates a pipe, a unidirectional data channel to be used for interprocess communication.
  * pipefd saves two new fd in [0] and [1], readend and writeend, respectibly;
  * 
  * returns 0 if success. -1 on error;
  */

/**
 * pid_t fork(void)
 * 
 * pid 0 = child;
 */

/**
* pid_t waitpid(pid_t pid, int *wstatus, int options)
* 
* waits process until the child pid changes status;
*/

/**
 * pid_t wait(int *wstatus)
 * 
 * waits process until the child pid termiantes;
 * 
 */

/**
 * int execve(const char *pathname, const char **argv, const char **envp)
 * 
 * executes the program referred on pathname. argv contains the arguments needed to execute
 * the program referred, argv[0] = pathname;
 * envp = main envp;
 */


/**
 * INFINITE CMD LIST
 * 
 * yes
 * 
 * cat (without input)
 *
 * while true; do ...; done
 *
 * sleep infinity (bash 5+)
 *
 * tail -f (following a file)
 *
 * ping (without count -c flag/argument)
 *
 * nc -lk (netcat listening mode)
 * 
 * watch (without exit condition)
 * 
 */ 