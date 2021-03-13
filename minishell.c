/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:20:03 by forsili           #+#    #+#             */
/*   Updated: 2021/03/13 21:43:03 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

t_cmds	init_cmd(t_cmds last)
{
	last.comand = malloc(1 * sizeof(t_scmd *));
	last.prev = 0;
	last.next = 0;
	last.comand[0] = 0;
	return (last);
}

int		signalaction = 0;

void	handlesignal(int signal)
{
	if (signal == SIGINT)
	{
		signalaction = 1;
	}
}

int		main_loop(t_h *h)
{
	char	*cmd;

	h->path = src_path(h->our_env);
		printf("sd\n");
	while (1)
	{
		if (signal(SIGINT, handlesignal) == SIG_ERR)
			write(2, "Error catching signal C \r\n", 26);
		if (signalaction == 1)
			signalaction = 0;
		src_usr(h->our_env, h);
		put_usrname(h->usr, h);
		ft_read_line(h);
		cmd = ft_strdup(h->buffer);
		parse_cmd(&cmd, h);
		//printercmds(esterna);
		//smister(esterna, h);
		free(cmd);
	}
}

int		main(int argc, char **argv, char **env)
{
	t_h		h;
	pid_t	pid;
	char	*tmp;

	ft_memset(&h, 0, sizeof(t_h));
	crt_env(env, &h);
	h.error = 0;
	h.cursor = 0;
	h.v_cursor = 0;
	tmp = malloc(FT_PATH_MAX + 7);
	tmp = getcwd(tmp, FT_PATH_MAX);
	h.history_path = ft_strjoin(tmp, "/.history");
	free(tmp);
	h.tmp_env = ft_calloc(ENV_SIZE, sizeof(char *));
	ft_convert_history(&h);
	main_loop(&h);
	return (0);
}
