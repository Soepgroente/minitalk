/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:18:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/07 21:34:29 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	i = 0;
	static char	c = 0;

	context = NULL;
	if (signal == SIGUSR2)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					i;
	struct sigaction	sa;
	int					error_check;

	i = 0;
	if (ft_printf("%d\n", getpid()) == -1)
		return (1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_NODEFER | SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sa.sa_sigaction = &signal_handler;
	error_check = sigaction(SIGUSR1, &sa, NULL);
	if (error_check == -1)
	{
		ft_printf("SIGUSR1 failed\n");
		exit(1);
	}
	error_check = sigaction(SIGUSR2, &sa, NULL);
	if (error_check == -1)
	{
		ft_printf("SIGUSR2 failed\n");
		exit(1);
	}
	while (1)
		pause();
}
