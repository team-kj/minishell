/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:57:09 by kycho             #+#    #+#             */
/*   Updated: 2020/12/17 15:57:27 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_dict **env, char *key)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(env[i]->key, key) == 0)
			return env[i]->value;
		i++;
	}
	return (NULL);
}
