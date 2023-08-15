#include "minitalk.h"

void	send_message(pid_t server_pid, char *message)
{
	char	*ptr;
	int		bit;

	ptr = message;
	while (*ptr)
	{
		bit = 0x80; // 10000000 in binary
		while (bit > 0)
		{
			if (*ptr & bit)
				kill(server_pid, SIGUSR1);
			else
				kill(server_pid, SIGUSR2);
			bit >>= 1;
			usleep(100); // Adjust as needed for communication speed
		}
		ptr++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [server_pid] [message]\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	message = argv[2];

	send_message(server_pid, message);

	return (0);
}
