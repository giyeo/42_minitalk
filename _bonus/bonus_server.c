/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_server.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:20:51 by rpaulino          #+#    #+#             */
/*   Updated: 2021/10/16 12:11:41 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_minitalk.h"

unsigned char	reverse(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return (b);
}

int	store_buffer(unsigned char byte)
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
		return (1);
	}
	buffer[i++] = byte;
	return (0);
}

void	byte_to_char(int sig)
{
	static unsigned char	x = 0;
	static int				i = 0;
	static int				confirm = 0;

	if (confirm)
		confirm = confirm_signal(sig);
	else
	{
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
			confirm = store_buffer(x);
			i = 0;
			x = 0;
		}
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
	struct sigaction	sigusr2;
	int					ret;
	int					pid;

	ret = -1;
	pid = getpid();
	print_pid(pid);
	sigusr1.sa_handler = &byte_to_char;
	sigusr2.sa_handler = &byte_to_char;
	while (ret == -1)
	{
		sigaction(SIGUSR1, &sigusr1, NULL);
		sigaction(SIGUSR2, &sigusr2, NULL);
		ret = pause();
	}
	return (0);
}
