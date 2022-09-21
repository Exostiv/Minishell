/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exostiv <exostiv@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:17:31 by kcatrix           #+#    #+#             */
/*   Updated: 2022/09/21 06:37:08 by exostiv          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**cmd_dollar_int(char **spli, int i)
{
	free(spli[i]);
	spli[i] = ft_mallocex(ft_itoa(g_stock.end), spli[i]);
	return (spli);
}

void	fix_out_inr_redir(void)
{
	g_stock.end = 0;
	if (g_stock.out > 1)
		close(g_stock.out);
	if (g_stock.in > 0)
		close(g_stock.in);
	if (g_stock.out != 1)
		dup2(0, STDOUT_FILENO);
	if (g_stock.in != 0)
		dup2(1, STDIN_FILENO);
}
