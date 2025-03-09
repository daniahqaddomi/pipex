/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:07:49 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/01/14 18:41:15 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_initialize(t_pipex *pipex, char *argv[], char *envp[])
{
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->infile = argv[1];
	pipex->outfile = argv[4];
	pipex->pipefd[0] = -1;
	pipex->pipefd[1] = -1;
	pipex->cmd = NULL;
	pipex->path = NULL;
	pipex->pip = 0;
	pipex->pos = 2;
	pipex->full_path = NULL;
	if (pipe(pipex->pipefd) == -1)
		ft_error(pipex, 1);
}

void	ft_execute(t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		ft_error(pipex, 1);
	else if (pipex->pid == 0)
	{
		if (pipex->pos == 2)
			child1(pipex);
		else
			child2(pipex);
		if (execve(pipex->full_path, pipex->cmd, pipex->envp) == -1)
		{
			ft_error(pipex, 1);
			exit(EXIT_FAILURE);
		}
	}
	parent(pipex);
}

void	child1(t_pipex *pipex)
{
	pipex->filefd = open(pipex->infile, O_RDONLY);
	if (pipex->filefd < 0)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		ft_error(pipex, 1);
	}
	if (dup2(pipex->filefd, STDIN_FILENO) == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		close(pipex->filefd);
		ft_error(pipex, 1);
	}
	close(pipex->filefd);
	if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		ft_error(pipex, 1);
	}
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	get_cmd(pipex);
}

void	child2(t_pipex *pipex)
{
	pipex->filefd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->filefd < 0)
	{
		close(pipex->pipefd[0]);
		ft_error(pipex, 1);
	}
	if (dup2(pipex->filefd, STDOUT_FILENO) == -1)
	{
		close(pipex->pipefd[0]);
		close(pipex->filefd);
		ft_error(pipex, 1);
	}
	close(pipex->filefd);
	if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipex->pipefd[0]);
		ft_error(pipex, 1);
	}
	close(pipex->pipefd[0]);
	get_cmd(pipex);
}

void	parent(t_pipex *pipex)
{
	if (pipex->pos == 2)
		close(pipex->pipefd[1]);
	else
		close(pipex->pipefd[0]);
	pipex->pos++;
	if (pipex->pos == 4)
	{
		parent_free(pipex);
		return ;
	}
	else
		ft_execute(pipex);
}
