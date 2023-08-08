/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:24:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/08 15:53:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	g_ready_to_send;

static void	confirm_signal(int signal)
{
	if (signal == SIGUSR1)
		g_ready_to_send = true;
}

static int	wait_for_reply(void)
{
	int	i;

	i = 0;
	while (1)
	{
		if (g_ready_to_send == true)
			return (0);
		usleep(10);
		i++;
		if (i == 100000)
			break ;
	}
	ft_printf("Server did not respond\n");
	return (-1);
}

static int	send_signal(char c, pid_t server_id, int *x, int *i)
{
	int	error_check;

	g_ready_to_send = false;
	if (((c >> *x) & 1) == 0)
		error_check = kill(server_id, SIGUSR1);
	else
		error_check = kill(server_id, SIGUSR2);
	if (error_check == -1)
	{
		ft_printf("Signal failed to send\n");
		return (-1);
	}
	(*x)++;
	if (*x == 8)
	{
		*x = 0;
		(*i)++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	int		x;
	pid_t	server_id;
	pid_t	client_id;

	i = 0;
	x = 0; 
	if (argc != 3)
		return (ft_printf("Input server PID and a string to send.\n"), 1);
	g_ready_to_send = true;
	client_id = getpid();
	server_id = ft_atoi(argv[1]);
	if (server_id <= 0)
		return (ft_printf("Invalid server id\n"), 1);
	signal(SIGUSR1, &confirm_signal);
	while (argv[2][i])
	{
		if (send_signal(argv[2][i], server_id, &x, &i) == -1)
			return (1);
		if (wait_for_reply() == -1)
			return (1);
	}
	return (0);
}
