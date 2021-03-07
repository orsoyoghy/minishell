/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: forsili <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:50:00 by forsili           #+#    #+#             */
/*   Updated: 2021/03/07 23:19:35 by forsili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		count_double_redir(t_h *h, int k, char **tmpcmd)
{
	h->ndoubler = 0;
	tmpcmd[k] = ft_strtrim(tmpcmd[k], " ");
	if (k != 0 && tmpcmd[k - 1][0] == '>' && tmpcmd[k - 1][1] == '>' && !tmpcmd[k - 1][2])
	{
		h->ndoubler += 2;
		h->fdred[k] = open(tmpcmd[k], O_RDWR);
		read_file(h, k);
		close(h->fdred[k]);
	}
	if (k < (arr_len(tmpcmd) - 2))
	{
		tmpcmd[k + 2] = ft_strtrim(tmpcmd[k + 2], " ");
		tmpcmd[k] = ft_strtrim(tmpcmd[k], " ");
		if (tmpcmd[k + 1][0] == '>' && tmpcmd[k + 1][1] == '>' && !tmpcmd[k + 1][2]
			&& ft_strncmp(tmpcmd[k], tmpcmd[k +2], ft_strlen(tmpcmd[k])))
		{
			h->ndoubler += 1;
			h->fdred[k] = open(tmpcmd[k + 2], O_RDWR | O_CREAT | O_APPEND);
		}
	}
	if (k == 0 && tmpcmd[k][0] == '>' && tmpcmd[k][1] == '>' && !tmpcmd[k][2])
	{
		tmpcmd[k + 1] = ft_strtrim(tmpcmd[k + 1], " ");
		h->fdred[k] = open(tmpcmd[k + 1], O_RDWR | O_CREAT | O_APPEND);
		close(h->fdred[k]);
	}
}

void		open_double_redir(t_h *h, int k)
{
	if (h->ndoubler == 1)
		dup2(h->fdred[k], 1);
	if (h->ndoubler == 3)
		write_file(h, k, h->bufred);
}

int			close_doubel_redir(t_h *h, int k, char **tmpcmd)
{
	if (h->ndoubler == 1 || h->ndoubler == 3)
	{
		close(h->fdred[k]);
	}
	return (k);
}