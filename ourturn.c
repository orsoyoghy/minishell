/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ourturn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 12:55:06 by sgiovo            #+#    #+#             */
/*   Updated: 2021/03/16 12:17:28 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_print_env(t_h *h)
{
	int		i;
	char	**envmtrx;

	i = 0;
	envmtrx = h->our_env;
	while (envmtrx[i])
		ft_printf("%s\n", envmtrx[i++]);
	return (0);
}

static int	ourturn_father4(t_h *h, char *cmd, char **argv)
{
	if ((ft_strncmp(argv[0], "exit", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("exit"))
	{
		if (arr_len(argv) > 2)
			free_exit(h, 255);
		if (arr_len(argv) == 1)
			free_exit(h, 0);
		if (ft_strdigit(argv[1]))
			free_exit(h, ft_atoi(argv[1]));
		else
			free_exit(h, 255);
	}
	cmd = NULL;
	return (0);
}

static int	ourturn_father3(t_h *h, char *cmd, char **argv)
{
	if ((ft_strncmp(argv[0], "export", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("export"))
	{
		if (!argv[1])
			h->error = ft_export(h);
		else
			h->error = ft_single_export(h, argv);
		return (1);
	}
	if ((ft_strncmp(argv[0], "unset", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("unset"))
	{
		if (argv[1])
			h->error = ft_unset_manager(h, argv);
		return (1);
	}
	return (ourturn_father4(h, cmd, argv));
}

static int	ourturn_father2(t_h *h, char *cmd, char **argv)
{
	int i;

	if ((ft_strncmp(argv[0], "stat", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("stat"))
	{
		i = 0;
		while (h->tmp_env[i])
		{
			printf("%s\n", h->tmp_env[i]);
			i++;
		}
		h->error = errno;
		return (1);
	}
	if ((ft_strncmp(argv[0], "setdir", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("setdir"))
	{
		h->sw_dir *= -1;
		h->error = errno;
		return (1);
	}
	return (ourturn_father3(h, cmd, argv));
}

int			ourturn_father(t_h *h, char *cmd, char **argv)
{
	int i;

	if ((ft_strncmp(argv[0], "cd", ft_strlen(argv[0])) == 0) &&
	ft_strlen(argv[0]) == ft_strlen("cd"))
	{
		h->error = cd(argv, h);
		return (1);
	}
	if (argv[0][0] != '=' && ft_strnstr(argv[0], "=", ft_strlen(argv[0])))
	{
		i = 0;
		while (argv[i] && argv[i][0] != '=' &&
		ft_strnstr(argv[i], "=", ft_strlen(argv[i])))
		{
			h->tmp_env[declarated(h->tmp_env, argv[i])] = ft_strdup(argv[i]);
			i++;
		}
		h->error = errno;
		return (1);
	}
	return (ourturn_father2(h, cmd, argv));
}
