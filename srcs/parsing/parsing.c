/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:23:23 by kycho             #+#    #+#             */
/*   Updated: 2021/01/24 02:02:17 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing(t_msh *msh, char *input)
{
	char *env_replaced_input;

	if (msh == NULL || input == NULL)
		return (ERROR);
	env_replaced_input = get_env_replaced_input(msh, input);
	split_token(env_replaced_input, &(msh->tokens), METACHARACTER);
	making_cmd(msh);
	free(env_replaced_input);
	return (SUCCESS);
}
