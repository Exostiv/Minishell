#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static void	ft_countquot(const char *s)
{
	int	i;
	int chkout;

	i = 0;
	chkout = 0;
	g_stock.chksimpl = 0;
	g_stock.chkdoubl = 0;
	while(s[i])
	{
		if((s[i] == '"' && g_stock.chksimpl == 0 && g_stock.chkdoubl == 0  && chkout == 0) ||
			(s[i] == '"' && chkout == 0 && (s[i -1] == '"' || s[i - 1]  == '\'')))
			g_stock.chkdoubl = g_stock.chkdoubl + 1;
		else if((g_stock.chkdoubl || g_stock.chksimpl > 0) && s[i] != '\'') 
			return ;
		if((s[i] == '\'' && g_stock.chksimpl == 0 && g_stock.chkdoubl == 0 && chkout == 0) ||
			(s[i] == '\'' && chkout == 0 && (s[i -1] == '"' || s[i - 1]  == '\'')))
			g_stock.chksimpl = g_stock.chksimpl + 1;
		else if((g_stock.chkdoubl || g_stock.chksimpl > 0) && s[i] != '"')
			return ;
		i++;
	}
}

static void	ft_subspli(const char *s)
{
	int	i;
	int x;

	i = 0;
	x = -1;
	g_stock.chkpospip = malloc(sizeof(int) * 10);
	while(s[i])
	{	
		if (s[i] == '"' || s[i] == '\'')
		{
			while(s[i] == '"' || s[i] == '\'')
				i++;
			while(s[i] && s[i] != '"' && s[i] != '\'')
			{	
				if (s[i] == '|')
					g_stock.chkpospip[++x] = i;
				i++;
			}
			while(s[i] == '"' || s[i] == '\'')
				i++;
		}
		i++;
	}
	g_stock.chkpospip[++x] = '\0';
}

static int	compte(const char *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_countquot(s);
	ft_subspli(s);
	while (s[i])
	{
		if (i == 0 && s[i] != c)
			j++;
		else if (s[i] != c && (i > 0 && s[i - 1] == c))
		{
			if (chkpospip((i - 1)) == 0)
				j++;
		}
		i++;
	}
	g_stock.nbpip = (j - 1);
	return (j);
}

static int	futur(const char *s, char c)
{
	int		i;

	g_stock.chks = 0;
	i = 0;
	while(s[i])
	{
		while (s[i] != c && s[i])
		{
			if (g_stock.chks > 0)
				g_stock.chks++;
			i++;
		}
		if (chkpospip((i)) != 0)
		{
			g_stock.chks++;
			i++;
		}
		else
		{
			return(i);
		}
	}
	return (i);
}

char	**ft_split_pipe(char const *s, char c)
{
	char	**a;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (0);
	j = compte((char *)s, c);
	a = malloc(sizeof(char *) * (j + 1));
	if (!a)
		return (0);
	i = 0;
	while (i < j)
	{
		k = 0;
		while (*s != '\0' && *s == c)
		{
			ft_augmentpospip();
			s++;
		}
		while(g_stock.chks-- > 0)
		{
			ft_augmentpospip();
			s++;
		}
		k = futur((char *)s, c);
		a[i] = ft_substr(s, 0, k);
		while (*s != '\0' && *s != c)
		{
			ft_augmentpospip();
			s++;
		}
		i++;
	}
	a[i] = NULL;
	return (a);
}