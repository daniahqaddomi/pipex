/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 20:54:31 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/01/13 19:41:40 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <libft.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**argv;
	int		pipefd[2];
	char	**cmd;
	char	**path;
	char	**envp;
	char	*full_path;
	int		i;
	int		pos;
	int		filefd;
	pid_t	pid;
	pid_t	pip;
}			t_pipex;

void		ft_initialize(t_pipex *pipex, char *argv[], char *envp[]);
int			ft_error(t_pipex *pipex, int flag);
void		find_path(t_pipex *pipex);
void		get_cmd(t_pipex *pipex);
void		get_cmd_path(t_pipex *pipex);
void		ft_execute(t_pipex *pipex);
void		child1(t_pipex *pipex);
void		child2(t_pipex *pipex);
void		parent(t_pipex *pipex);
void		close_command(t_pipex *pipex);
void		parent_free(t_pipex *pipex);
void		child_free(t_pipex *pipex);
int			main(int argc, char **argv, char **envp);
void		free_path(char **path);
void		ft_access(t_pipex *pipex);

#endif