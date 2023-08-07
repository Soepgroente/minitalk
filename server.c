/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/04 13:18:39 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/07/31 12:28:04 by vvan-der      ########   odam.nl         */
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
		if (c == '\0')
			return ;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	int					i;
	struct sigaction	sa;

	i = 0;
	if (ft_printf("%d\n", getpid()) == -1)
		return (1);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_handler = SIG_IGN;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
