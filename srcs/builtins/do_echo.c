/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiseo <jiseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:51:59 by jiseo             #+#    #+#             */
/*   Updated: 2020/12/17 12:52:01 by jiseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		do_echo(t_msh *msh, int fd)
{
	int		idx;
	
	idx = 1;
	while (idx < msh->cmds->length)
	{
		ft_putstr_fd(msh->cmds->args[idx], fd);
		ft_putchar_fd(' ', fd);
		idx++;
	}
	ft_putchar_fd('\n', fd);
}
