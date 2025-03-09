/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:09:05 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/01/14 18:32:20 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(t_pipex *pipex, int flag)
{
	child_free(pipex);
	if (flag == 127)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(pipex->argv[pipex->pos], 2);
		exit(127);
	}
	else if (flag == 126)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(pipex->argv[pipex->pos], 2);
		exit(126);
	}
	else if (flag == 128)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(pipex->argv[pipex->pos], 2);
		exit(127);
	}
	else
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (pipex == NULL)
		return ;
	if (pipex->cmd)
	{
		while (pipex->cmd[i])
			free(pipex->cmd[i++]);
		free(pipex->cmd);
		pipex->cmd = NULL;
	}
	if (pipex->full_path)
		free(pipex->full_path);
	pipex->full_path = NULL;
	i = 0;
	if (pipex->path)
	{
		while (pipex->path[i])
			free(pipex->path[i++]);
		free(pipex->path);
		pipex->path = NULL;
	}
}

void	parent_free(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	close_command(pipex);
}

void	close_command(t_pipex *pipex)
{
	if (pipex == NULL)
		return ;
	if (pipex->pipefd[0] >= 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0)
		close(pipex->pipefd[1]);
	if (pipex->pip >= 0)
		close(pipex->pip);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	path = NULL;
}
