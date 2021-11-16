/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:20:57 by rpaulino          #+#    #+#             */
/*   Updated: 2021/11/14 22:40:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
		usleep(600);
	}
	return (x);
}

int	main(int argc, char *argv[])
{
	unsigned char	n;
	char			*text;
	int				pid;

	if(argc < 3)
		exit(0);
	pid = ft_atoi(argv[1]);
	text = argv[2];
	while (*text != '\0')
		n = char_to_byte(*(text++), pid);
	char_to_byte('\n', pid);
}
