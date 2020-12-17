/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiseo <jiseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 02:36:28 by jiseo             #+#    #+#             */
/*   Updated: 2020/12/17 12:45:04 by jiseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_STRUCT_H
# define MSH_STRUCT_H

# define FALSE 0
# define TRUE 1

# define SUCCESS 1
# define ERROR -1

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define EXEC_IDX 0

# define TYPE_DEFAULT 0
# define TYPE_PIPE 1

# define METACHARACTER " \t\n|;<>"

typedef struct		s_cmd
{
	char			**args;
	int				length;
	int				type;
	int				pipes[2];
	t_list			*redirection_files;
	struct s_cmd	*previous;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_dict
{
	char			*key;
	char			*value;
}					t_dict;

typedef struct		s_msh
{
	char			*program_name;
	int				exit_status;
	t_list			*tokens;
	t_cmd			*cmds;
	t_dict			**env;
	int				env_len;
	char			**path;
	char			*wd;
}					t_msh;

enum
{
	k_cd = 1,
	k_echo = 2,
	k_env = 3,
	k_export = 4,
	k_pwd = 5,
	k_unset = 6,
	k_exit = 7
};
#endif