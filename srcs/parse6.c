/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:56:45 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/05 14:36:10 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*verif_chev3bis(char *str, char *tmp, int i, int j)
{
	g_stock.chevquote = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && g_stock.chevquote == 0)
			g_stock.chevquote = 1;
		else if ((str[i] == '\"' || str[i] == '\'') && g_stock.chevquote == 1)
			g_stock.chevquote = 0;
		if (i >= 1 && (str[i] == '>' || str[i] == '<')
			&& (str[i - 1] != '>' && str[i - 1] != '<'
				&& g_stock.chevquote == 0))
			tmp[j++] = 32;
		else if (i >= 1 && (str[i - 1] == '>' || str[i - 1] == '<')
			&& (str[i] != '>' && str[i] != '<'
				&& str[i] && g_stock.chevquote == 0))
			tmp[j++] = 32;
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

void	verif_chev2bis2(void)
{
	char	*tmp;
	int		i;

	tmp = "newline";
	i = 0;
	while (tmp[i])
	{
		g_stock.chev[i] = tmp[i];
		i++;
	}
	g_stock.chev[i] = '\0';
}

int	ft_errorchev(char *str)
{
	free(g_stock.chev);
	g_stock.chev = malloc(sizeof(char) * 2);
	g_stock.chev[0] = str[g_stock.lastposchev];
	g_stock.chev[1] = '\0';
	return (0);
}

char	*fixchev(char *line)
{
	printf("bash: syntax error near unexpected token `%s'\n", g_stock.chev);
	free(line);
	return (" ");
}
