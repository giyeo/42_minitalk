/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:20:57 by rpaulino          #+#    #+#             */
/*   Updated: 2021/10/16 12:08:07 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_minitalk.h"

unsigned char	char_to_byte(unsigned char a, int pid)
{
	unsigned char	x;
	int				i;

	x = 0;
	i = 0;
	while (i++ < 8)
	{
		if (a % 2 == 0 || a == 0)
		{
			if (a != 0)
				a /= 2;
			x <<= 1;
			kill(pid, SIGUSR1);
		}
		else
		{
			a /= 2;
			x <<= 1;
			x += 1;
			kill(pid, SIGUSR2);
		}
		usleep(1000);
	}
	return (x);
}

void	confirm_signal_client(int sig)
{
	char	*done;

	done = "Signal Received.\n";
	write(1, done, 18);
}

int	main(int argc, char *argv[])
{
	struct sigaction	sigusr1;
	unsigned char		n;
	char				*text;
	int					pid;
	char				*my_pid;
	
	if(argc < 3)
		exit(0);
	sigusr1.sa_handler = &confirm_signal_client;
	pid = ft_atoi(argv[1]);
	text = argv[2];
	while (*text != '\0')
		n = char_to_byte(*(text++), pid);
	char_to_byte('\n', pid);
	my_pid = ft_itoa(getpid());
	while (*my_pid != '\0')
		n = char_to_byte(*(my_pid++), pid);
	char_to_byte('\n', pid);
	sigaction(SIGUSR1, &sigusr1, NULL);
}
