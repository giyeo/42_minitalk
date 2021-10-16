/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_confirm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:20:51 by rpaulino          #+#    #+#             */
/*   Updated: 2021/10/16 12:13:47 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_minitalk.h"

int	store_buffer_pid(unsigned char byte)
{
	static int	i = 0;
	static char	buffer[5000];
	char		temp;
	int			x;

	x = 0;
	if (byte == '\n')
	{
		buffer[i++] = '\n';
		buffer[i] = '\0';
		i = 0;
		kill(ft_atoi(buffer), SIGUSR1);
		return (0);
	}
	buffer[i++] = byte;
	return (1);
}

int	confirm_signal(int sig)
{
	static unsigned char	x = 0;
	static int				i = 0;
	int						temp;
	if (sig == SIGUSR1)
		x <<= 1;
	else if (sig == SIGUSR2)
	{
		x <<= 1;
		x += 1;
	}
	if (i++ == 7)
	{
		x = reverse(x);
		temp = store_buffer_pid(x);
		i = 0;
		x = 0;
		return (temp);
	}
}
