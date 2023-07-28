/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:24:23 by vvan-der          #+#    #+#             */
/*   Updated: 2023/07/06 19:49:10 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_exit(void)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	send_signal(char signal, int pid)
{
	int	i;

	i = 7;
	pid = 0;
	puts("\n");
	while (i >= 0)
	{
		// if (((signal >> i) & 1 ) == 0)
		// 	kill(pid, SIGUSR1);
		// else
		// 	kill(pid, SIGUSR2);
		printf("Bit [%d]: %d\n", i, (signal >> i) & 1);
		i--;
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	int		pid;

	if (argc != 3)
	{
		ft_putendl_fd("Input error. Input server PID \
		and a string to send", STDERR_FILENO);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	str = ft_strdup(argv[2]);
	if (!str)
		ft_exit();
	while (*str)
	{
		send_signal(*str, pid);
		str++;
	}
}
