/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luibarbo <luibarbo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:29:47 by luibarbo          #+#    #+#             */
/*   Updated: 2024/07/12 16:02:58 by luibarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "ft_printf.h"
#include "libft.h"

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

void	append_char(char c)
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
		ft_printf("%s\n", buffer);
		free (buffer);
		buffer = NULL;
		current_length = 0;
		length = 1024;
	}
}

void	sig_handle(int sig)
{
	static int				i = 0;
	static unsigned char	c = 0;

	if (sig == SIGUSR2)
		c = c << 1;
	else if (sig == SIGUSR1)
		c = (c << 1) | 1;
	i++;
	if (i == 8)
	{
		append_char(c);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("PID: %d\n", getpid());
	action.sa_handler = sig_handle;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause ();
	return (0);
}
