/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_minitalk.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpaulino <rpaulino@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 11:58:57 by rpaulino          #+#    #+#             */
/*   Updated: 2021/10/16 12:12:39 by rpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		confirm_signal(int sig);
unsigned char	reverse(unsigned char b);
#endif