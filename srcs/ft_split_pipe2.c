#include "../includes/minishell.h"

int chkpospip(int i)
{
    int y;

    y = 0;
    while(g_stock.chkpospip[y])
    {
        if(g_stock.chkpospip[y] == i)
            return (1);
        y++;
    }
    return (0);
}

void    ft_augmentpospip(void)
{
    int i;

    i = 0;
    while(g_stock.chkpospip[i])
    {
        g_stock.chkpospip[i] = g_stock.chkpospip[i] - 1;
        i++;
    }
}