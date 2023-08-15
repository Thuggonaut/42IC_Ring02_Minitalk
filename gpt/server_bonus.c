#include "minitalk_bonus.h"

volatile sig_atomic_t	g_received_char = 0;
volatile sig_atomic_t	g_received_bits = 0;

void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		g_received_char |= (1 << g_received_bits);
	g_received_bits++;
}

void	print_received_char(void)
{
	write(1, &g_received_char, 1);
	g_received_char = 0;
	g_received_bits = 0;
}

int	main(void)
{
	struct sigaction	sigact;

	sigact.sa_flags = 0;
	sigact.sa_handler = sig_handler;
	sigemptyset(&sigact.sa_mask);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);

	ft_putnbr_fd(getpid(), 1); // Print server's PID
	write(1, "\n", 1); // Newline after PID

	while (1)
	{
		if (g_received_bits == 8)
			print_received_char();
		usleep(50); // Adjust as needed for communication speed
	}

	return (0);
}
