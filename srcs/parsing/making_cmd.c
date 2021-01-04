/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kycho <kycho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 18:34:02 by kycho             #+#    #+#             */
/*   Updated: 2021/01/04 12:47:06 by kycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*get_new_cmd(t_cmd *previous)
{
	t_cmd	*new_cmd;

	if (!(new_cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		exit_print_err(strerror(errno));
	if (!(new_cmd->args = (char**)malloc(sizeof(char*))))
		exit_print_err(strerror(errno));
	new_cmd->args[0] = NULL;
	new_cmd->length = 0;
	new_cmd->type = TYPE_DEFAULT;
	new_cmd->pipes[0] = -1;
	new_cmd->pipes[1] = -1;
	new_cmd->redirection_files = NULL;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->prev = NULL;
	new_cmd->next = NULL;
	if (previous != NULL)
	{
		previous->next = new_cmd;
		new_cmd->prev = previous;
	}
	return (new_cmd);
}

void	add_args(t_cmd *cmd, t_list *token, t_msh *msh)
{
	int		i;
	char	**tmp;

	if (!(tmp = (char**)malloc(sizeof(char*) * (cmd->length + 2))))
		exit_print_err(strerror(errno));
	tmp[cmd->length + 1] = NULL;
	i = 0;
	while (i < cmd->length)
	{
		tmp[i] = cmd->args[i];
		i++;
	}
	sanitize_token(token, msh);
	tmp[i] = token->content;
	free(cmd->args);
	cmd->args = tmp;
	cmd->length++;
}

void	add_redirection_file(t_cmd *cmd, t_list **token, t_msh *msh)
{
	t_list *lstnew;

	sanitize_token(*token, msh);
	if (!(lstnew = ft_lstnew((*token)->content)))
		exit_print_err(strerror(errno));
	if (cmd->redirection_files == NULL)
		cmd->redirection_files = lstnew;
	else
		ft_lstadd_back(&cmd->redirection_files, lstnew);
	*token = (*token)->next;
	sanitize_token(*token, msh);
	if (!(lstnew = ft_lstnew((*token)->content)))
		exit_print_err(strerror(errno));
	ft_lstadd_back(&cmd->redirection_files, lstnew);
}

void	making_cmd(t_msh *msh)
{
	t_cmd	*cmd;
	t_list	*token;

	cmd = get_new_cmd(NULL);
	msh->cmds = cmd;
	token = msh->tokens;
	while (token)
	{
		if (ft_strcmp(";", token->content) == 0 && token->next != NULL)
			cmd = get_new_cmd(cmd);
		else if (ft_strcmp("|", token->content) == 0)
		{
			cmd->type = TYPE_PIPE;
			cmd = get_new_cmd(cmd);
		}
		else if (ft_strcmp("<", token->content) == 0 ||
				ft_strcmp(">", token->content) == 0 ||
				ft_strcmp(">>", token->content) == 0)
			add_redirection_file(cmd, &token, msh);
		else if (ft_strcmp(";", token->content) != 0)
			add_args(cmd, token, msh);
		token = token->next;
	}
}
