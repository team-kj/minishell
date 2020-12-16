/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiseo <jiseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:57:53 by jiseo             #+#    #+#             */
/*   Updated: 2020/12/15 03:48:09 by jiseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		do_cd(t_msh *msh)
{
	char	*str;

	if (msh->cmd_list[msh->cmd_idx + 1] == NULL)
	{
		chdir("/home/jiseo"); // HOME
		return ;
	}
	str = msh->cmd_list[++msh->cmd_idx];
	if (!ft_strcmp("-", str))
	{
		chdir("/home/jiseo/work"); // OLDPWD
		return ;
	}
	chdir(str);
	/*
		str = ft_strdup();
		i = chdir(str);
		if (i == 0)
			success;
		else if (i == -1)
			fail;
		free(str);
	*/ 
}