/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:29:47 by luibarbo          #+#    #+#             */
/*   Updated: 2024/08/01 10:50:22 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf.h"
#include "libft.h"

static void	ft_free(char **buffer, size_t *length, size_t *current_length)
{
	free (*buffer);
	*buffer = NULL;
	*current_length = 0;
	*length = 1024;
}

static char	*resize_buffer(char *buffer, size_t *length, size_t current_length)
{
	char	*new_buffer;

	*length *= 2;
	new_buffer = ft_calloc(*length, sizeof(char));
	if (!new_buffer)
	{
		free (buffer);
		return (NULL);
	}
	ft_memcpy(new_buffer, buffer, current_length);
	free (buffer);
	return (new_buffer);
}

void	append_char(char c, int client_pid)
{
	static size_t	length = 1024;
	static size_t	current_length = 0;
	static char		*buffer = NULL;

	if (buffer == NULL)
	{
		buffer = ft_calloc(length, sizeof(char));
		if (!buffer)
			return ;
	}
	if (current_length + 1 >= length)
	{
		buffer = resize_buffer(buffer, &length, current_length);
		if (!buffer)
			return ;
	}
	buffer[current_length++] = c;
	if (c == '\0')
	{
		kill(client_pid, SIGUSR1);
		ft_printf("%s\n", buffer);
		ft_free(&buffer, &length, &current_length);
	}
}

void	sig_handle(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static unsigned char	c = 0;
	static int				client_pid = 0;

	(void)context;
	client_pid = info->si_pid;
	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		append_char(c, client_pid);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("PID: %d\n", getpid());
	action.sa_sigaction = sig_handle;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause ();
	return (0);
}
