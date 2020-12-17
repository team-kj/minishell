/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiseo <jiseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 05:44:26 by jiseo             #+#    #+#             */
/*   Updated: 2020/12/17 12:37:53 by jiseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_envjoin(t_dict **env, int env_len)
{
	char	**temp;
	int		idx;

	if (!(temp = (char **)malloc(sizeof(char *) * (env_len + 1))))
		exit_print_err(strerror(errno));
	idx = 0;
	while (idx < env_len)
	{
		if (!(temp[idx] = ft_strjoin3(env[idx]->key, "=", env[idx]->value)))
			exit_print_err(strerror(errno));
		idx++;
	}
	temp[idx] = NULL;
	return (temp);
}

void	exec_process(t_msh *msh, char **av, char **env)
{
	char		*temp;
	int			idx;
	int			ret;

	idx = 0;
	while (msh->path[idx])
	{
		if (!(temp = ft_strjoin3(msh->path[idx], "/", msh->cmds->args[0])))
			exit_print_err(strerror(errno));
		ret = execve(temp, av, env);
		if (ret == -1)
			exit_print_err(strerror(errno));
		free(temp);
		idx++;
	}
	ft_double_free((void **)av);
	ft_double_free((void **)env);
}

void	executor(t_msh *msh)
{
	pid_t		pid;
	char		**av;
	char		**env;
	int			idx;

	if (!(av = (char **)malloc(sizeof(char *) * (msh->cmds->length + 1))))
		exit_print_err(strerror(errno));
	if (!(av[0] = ft_strjoin("./", msh->cmds->args[0])))
		exit_print_err(strerror(errno));
	idx = -1;
	while (++idx < msh->cmds->length)
		if (!(av[idx] = ft_strdup(msh->cmds->args[idx])))
			exit_print_err(strerror(errno));
	av[idx] = NULL;
	env = ft_envjoin(msh->env, msh->env_len);
	pid = fork();
	if (pid == 0)
	{
		exec_process(msh, av, env);
		exit(EXIT_SUCCESS);
	}
	else
		wait(NULL);
}
