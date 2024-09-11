/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:29:39 by luibarbo          #+#    #+#             */
/*   Updated: 2024/07/12 16:03:00 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"
#include "ft_printf.h"

int	is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	usleep_time(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len >= 19000)
		return (1000);
	if (len >= 10000)
		return (500);
	if (len >= 5000)
		return (300);
	return (150);
}

void	send_sig(int pid, char *s)
{
	int	c;
	int	i;
	int	time;

	time = usleep_time(s);
	while (*s)
	{
		i = -1;
		c = *s;
		while (++i < 8)
		{
			if (((c >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR1);
			else if (((c >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR2);
			usleep(time);
		}
		s++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR2);
		usleep(time);
	}
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("Invalid number of arguments!\n");
		ft_printf("Format : './client <Process ID (PID)> <MESSAGE>'\n");
		exit (1);
	}
	if (!is_number(argv[1]))
	{
		ft_printf("Error: Invalid PID!\n");
		exit (1);
	}
	send_sig(ft_atoi(argv[1]), argv[2]);
	return (0);
}
