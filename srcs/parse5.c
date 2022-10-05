/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicoue <tnicoue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 09:51:13 by tnicoue           #+#    #+#             */
/*   Updated: 2022/10/05 14:31:27 by tnicoue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*verif_chev(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	j = 0;
	i = 0;
	if (verif_chev2(str, i, j) == 0)
		return (0);
	return (verif_chev3(str, tmp, i, j));
}

int	verif_chev2(char *str, int i, int j)
{
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			while ((str[i] == '>' || str[i] == '<' || str[i] == 32
					|| (str[i] >= 9 && str[i] <= 13)) && j < 3)
			{
				if (str[i] == '>' || str[i] == '<')
				{
					g_stock.lastposchev = i;
					j++;
				}
				i++;
			}
			if (j == 3)
				return (ft_errorchev(str));
			j = 0;
		}
		i++;
	}
	i = 0;
	if (verif_chev2bis(str, i) == 0)
		return (0);
	return (1);
}

int	verif_chev2bis(char *str, int i)
{
	while (str[i])
		i++;
	i--;
	while (i > 0 && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i--;
	if (str[i] == '<' || str[i] == '>')
	{
		free(g_stock.chev);
		g_stock.chev = malloc(sizeof(char) * 8);
		verif_chev2bis2();
		return (0);
	}
	return (1);
}

char	*verif_chev3(char *str, char *tmp, int i, int j)
{
	g_stock.chevquote = 0;
	while (str[i])
	{
		if ((str[i] == '\"' || str[i] == '\'') && g_stock.chevquote == 0)
			g_stock.chevquote = 1;
		else if ((str[i] == '\"' || str[i] == '\'') && g_stock.chevquote == 1)
			g_stock.chevquote = 0;
		if ((str[i + 1] == '>' || str[i + 1] == '<')
			&& (str[i] != '>' && str[i] != '<') && g_stock.chevquote == 0)
				j++;
		if ((str[i] == '>' || str[i] == '<')
			&& (str[i + 1] != '>' && str[i + 1] != '<' && str[i + 1])
			&& g_stock.chevquote == 0)
				j++;
		i++;
	}
	i = 0;
	if (j > 0)
		tmp = malloc(sizeof(char) * (ft_strlen(str) + j + 1));
	else
		return (str);
	j = 0;
	str = verif_chev3bis(str, tmp, i, j);
	return (str);
}
