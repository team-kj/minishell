/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:40:41 by kycho             #+#    #+#             */
/*   Updated: 2021/01/17 21:52:08 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sanitize_env_sub(char **res_str, char *og_str, t_msh *msh, char *tmp)
{
	if (og_str[1] == '$' || ('1' <= og_str[1] && og_str[1] <= '9'))
		return (2);
	else if (og_str[1] == '"' || og_str[1] == '\'')
		return (1);
	else if (og_str[1] == '0')
	{
		if (!(tmp = ft_strjoin(*res_str, msh->program_name)))
			exit_print_err(strerror(errno));
		free(*res_str);
		*res_str = tmp;
		return (2);
	}
	else if (og_str[1] == '?')
	{
		if (!(tmp = ft_strjoin(*res_str, ft_itoa(msh->exit_status))))
			exit_print_err(strerror(errno));
		free(*res_str);
		*res_str = tmp;
		return (2);
	}
	else if (!(og_str[1] != '\0' && (og_str[1] == '_' 
					|| ('0' <= og_str[1] && og_str[1] <= '9')
					|| ('a' <= og_str[1] && og_str[1] <= 'z')
					|| ('A' <= og_str[1] && og_str[1] <= 'Z'))))
	{
		append_char_to_str(res_str, '$');
		return (1);
	}
	return (-1);
}

int		sanitize_env(char **res_str, char *og_str, t_msh *msh, int in_dquotes)
{
	int		env_len;
	char	*env_key;
	t_dict	*env_dict;
	char	*tmp;
	char	*tmp2;

	if ((env_len = sanitize_env_sub(res_str, og_str, msh, NULL)) != -1)
		return (env_len);
	
	
	env_len = 1;
	while (og_str[env_len] != '\0' && (og_str[env_len] == '_'
				|| ('0' <= og_str[env_len] && og_str[env_len] <= '9')
				|| ('a' <= og_str[env_len] && og_str[env_len] <= 'z')
				|| ('A' <= og_str[env_len] && og_str[env_len] <= 'Z')))
		env_len++;
	if (!(env_key = (char *)malloc(sizeof(char) * (env_len + 1))))
		exit_print_err(strerror(errno));
	ft_strlcpy(env_key, og_str + 1, env_len);


	env_dict = get_env_dict(msh->env, env_key);
	free(env_key);
	if (env_dict == NULL || env_dict->value == NULL)
		return (env_len);
	if (in_dquotes)
	{
		if (!(tmp2 = insert_char_before_set(env_dict->value, "\"\\", '\\')))
			exit_print_err(strerror(errno));
	}
	else
	{
		if (!(tmp2 = insert_char_before_set(env_dict->value, "'\"\\", '\\')))
			exit_print_err(strerror(errno));
	}
	if (!(tmp = ft_strjoin(*res_str, tmp2)))
		exit_print_err(strerror(errno));
	free(tmp2);
	free(*res_str);
	*res_str = tmp;
	return (env_len);
}
