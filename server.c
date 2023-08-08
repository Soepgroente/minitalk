/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:18:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/08 16:40:00 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_data	g_data;

static int	init_data(void)
{
	g_data.i = 0;
	g_data.bit = 0;
	g_data.size = 2;
	g_data.c = '\0';
	g_data.ready_to_send = false;
	g_data.msg = (char *) ft_calloc(g_data.size, sizeof(char));
	if (g_data.msg == NULL)
		return (-1);
	return (0);
}

static bool	wait_for_end(void)
{
	int	i;

	i = 0;
	while (1)
	{
		if (g_data.ready_to_send == true)
			return (false);
		usleep(10);
		i++;
		if (i == 1000)
			return (true);
	}
}

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	context = NULL;
	if (g_data.i + 1 >= g_data.size)
	{
		g_data.size *= 2;
		g_data.msg = ft_realloc(g_data.msg, g_data.size);
	}
	if (signal == SIGUSR2)
		g_data.c = g_data.c | (1 << g_data.bit);
	g_data.ready_to_send = true;
	g_data.bit++;
	if (g_data.bit == 8)
	{
		g_data.msg[g_data.i] = g_data.c;
		g_data.i++;
		g_data.bit = 0;
		g_data.c = '\0';
		g_data.ready_to_send = false;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	int					error_check;

	if (ft_printf("%d\n", getpid()) == -1)
		return (1);
	g_data.msg = NULL;
	if (init_data() == -1)
		return (ft_printf("Malloc error\n"), 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_NODEFER | SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sa.sa_sigaction = &signal_handler;
	error_check = sigaction(SIGUSR1, &sa, NULL);
	error_check = sigaction(SIGUSR2, &sa, NULL);
	if (error_check == -1)
		return (ft_printf("Sigaction failed\n"), 1);
	while (1)
	{
		if (g_data.i > 0 && wait_for_end() == true)
		{
			ft_putstr_fd(g_data.msg, STDOUT_FILENO);
			free(g_data.msg);
			g_data.msg = NULL;
			if (init_data() == -1)
				return (ft_printf("Malloc error\n"), 1);
		}
	}
}
