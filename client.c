/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:24:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/07 11:11:17 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	signal_num;

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	
	if (signal == SIGUSR1)
		return (true);
	else
		return (false);
}

static void	send_signal(int signal, siginfo_t *info, void *context)
{
	context = NULL;
	if (signal_num == 0)
		kill(info->si_pid, SIGUSR1);
	else if (signal_num == 1)
		kill(info->si_pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	int					i;
	pid_t				server_id;
	pid_t				client_id;
	struct sigaction	sa;
	bool				ready_to_send;

	i = 0;
	signal_num = 0;
	if (argc != 3)
	{
		ft_printf("Input error. Input server PID and a string to send.\n");
		return (1);
	}
	client_id = getpid();
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0)
	{
		ft_printf("Invalid server id\n");
		return (1);
	}
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sa.sa_sigaction = send_signal;
	sigaction(SIGUSR1, &sa, &ready_to_send);
	while (argv[2][i])
	{
		if (ready_to_send == true)
		{
			send_signal(argv[2][i], server_id);
			i++;
			ready_to_send = false;
		}
	}
}
