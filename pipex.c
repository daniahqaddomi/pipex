/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dqaddomi <dqaddomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:32:53 by dqaddomi          #+#    #+#             */
/*   Updated: 2025/01/14 16:18:03 by dqaddomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->argv[pipex->pos][i] && pipex->argv[pipex->pos][i] == ' ')
		i++;
	if (i == ft_strlen(pipex->argv[pipex->pos]))
		ft_error(pipex, 127);
	pipex->cmd = ft_split(pipex->argv[pipex->pos], ' ');
	if (!pipex->cmd[0] || !pipex->cmd)
		ft_error(pipex, 127);
	if (ft_strchr(pipex->cmd[0], '/'))
		ft_access(pipex);
	else
		get_cmd_path(pipex);
}

void	ft_access(t_pipex *pipex)
{
	char	*tmp;

	if (access(pipex->cmd[0], F_OK) == 0)
	{
		if (access(pipex->cmd[0], R_OK | X_OK) == 0)
		{
			pipex->full_path = ft_strdup(pipex->cmd[0]);
			tmp = ft_strdup(ft_strrchr(pipex->cmd[0], '/') + 1);
			free(pipex->cmd[0]);
			pipex->cmd[0] = tmp;
			return ;
		}
		ft_error(pipex, 126);
	}
	ft_error(pipex, 128);
}

void	find_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	if (!pipex || !pipex->envp)
		ft_error(pipex, 1);
	while (pipex->envp[i] && ft_strncmp(pipex->envp[i], "PATH=", 5) != 0)
		i++;
	if (!pipex->envp[i])
		ft_error(pipex, 1);
	pipex->path = ft_split(pipex->envp[i] + 5, ':');
	if (!pipex->path)
		ft_error(pipex, 1);
}

void	get_cmd_path(t_pipex *pipex)
{
	char	*slash;

	pipex->i = 0;
	find_path(pipex);
	while (pipex->path[pipex->i])
	{
		slash = ft_strjoin(pipex->path[pipex->i], "/");
		if (!slash)
			ft_error(pipex, 1);
		pipex->full_path = ft_strjoin(slash, pipex->cmd[0]);
		free(slash);
		if (!pipex->full_path)
			ft_error(pipex, 1);
		if (access(pipex->full_path, F_OK) == 0)
		{
			if (access(pipex->full_path, R_OK | X_OK) == 0)
				return ;
			ft_error(pipex, 126);
		}
		if (pipex->full_path)
			free(pipex->full_path);
		pipex->full_path = NULL;
		pipex->i++;
	}
	ft_error(pipex, 127);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid;
	int		exit;
	int		exit_status;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments\n", 1);
		return (1);
	}
	ft_initialize(&pipex, argv, envp);
	ft_execute(&pipex);
	parent_free(&pipex);
	while (pipex.pos-- > 0)
	{
		pid = wait(&exit_status);
		if (pid == pipex.pid)
		{
			if (WIFEXITED(exit_status))
				exit = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				exit = 128 + WTERMSIG(exit_status);
		}
	}
	return (exit);
}
