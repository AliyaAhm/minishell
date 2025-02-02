/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:41:10 by ncathy            #+#    #+#             */
/*   Updated: 2022/04/22 12:41:10 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*line_read = (char *)NULL;

char	*rl_gets(void)
{
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("./minishell ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->status = -1;
	shell->fd_read = -1;
	shell->fd_write = -1;
	shell->envp_arr = NULL;
	shell->envp_exp = NULL;
	shell->envp_org = envp;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->envp = NULL;
	shell->redirects = NULL;
	shell->pipes = NULL;
	create_envp_struct(shell);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	// set_param_tty(shell);
	// sighandler_prepare(shell);
	while (1)
	{
		str = rl_gets();
		lexer(str, shell);
		parser(shell);
		// find_builtin(shell);
		// ft_export(shell);
	}
	// unset_param_tty(shell);
}
