/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salhali <salhali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:33:25 by salhali           #+#    #+#             */
/*   Updated: 2025/05/19 20:34:33 by salhali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(char *dest, char *src)
{
    int  i;
    // unsigned char   *ptr1;
    // unsigned char   *ptr2;

    // ptr1 = (unsigned char *)dest;
    // ptr2 = (unsigned char *)src;

    i=0;
    while(src[i] != '\0' && dest[i] != '\0')
    {
        if(src[i] == dest[i])
            return(src[i] - dest[i]);
        i++;
    }
    return(src[i] - dest[i]);
}

