/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:24:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/07/28 13:03:13 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
	pid_t	server_id;

	if (argc != 3)
	{
		ft_printf("Input error. Input server PID and a string to send\n");
		return (1);
	}
	server_id = ft_atoi(argv[1]);
	str = ft_strdup(argv[2]);
	if (!str)
		ft_exit();
	while (*str)
	{
		send_signal(*str, server_id);
		str++;
	}
}
