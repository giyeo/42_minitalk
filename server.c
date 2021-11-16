/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:20:51 by rpaulino          #+#    #+#             */
/*   Updated: 2021/11/14 23:34:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char	reverse(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return (b);
}

void	store_buffer(unsigned char byte)
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
		while (buffer[x] != '\0')
		{
			temp = buffer[x++];
			write(1, &temp, 1);
		}
		i = 0;
		return ;
	}
	buffer[i++] = byte;
}

void	byte_to_char(int sig)
{
	static unsigned char	x = 0;
	static int				i = 0;

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
		store_buffer(x);
		i = 0;
		x = 0;
	}
}

void	print_pid(int pid)
{
	char	*string;
	char	*str_pid;
	char	temp;

	string = "PID: ";
	str_pid = ft_itoa(pid);
	while (*string != '\0')
	{
		temp = *string++;
		write(1, &temp, 1);
	}
	while (*str_pid != '\0')
	{
		temp = *str_pid++;
		write(1, &temp, 1);
	}
	temp = '\n';
	write(1, &temp, 1);
}

int	main(void)
{
	struct sigaction	sigusr1;
	int					pid;

	pid = getpid();
	print_pid(pid);
	sigusr1.sa_handler = &byte_to_char;
	while (1)
	{
		sigaction(SIGUSR1, &sigusr1, NULL);
		sigaction(SIGUSR2, &sigusr1, NULL);
		pause();
	}
	return (0);
}
