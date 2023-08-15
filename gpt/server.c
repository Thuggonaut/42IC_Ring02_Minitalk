#include "minitalk.h"

volatile sig_atomic_t	g_received_char = 0;

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_received_char <<= 1;
	else if (sig == SIGUSR2)
	{
		g_received_char <<= 1;
		g_received_char |= 1;
	}
}

void	print_received_char(void)
{
	write(1, &g_received_char, 1);
	g_received_char = 0;
}

int	main(void)
{
	struct sigaction	sigact;

	sigact.sa_flags = 0;
	sigact.sa_handler = sig_handler;
	sigemptyset(&sigact.sa_mask);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);

	while (1)
	{
		usleep(50); // Adjust as needed for communication speed
		if (g_received_char)
			print_received_char();
	}

	return (0);
}
