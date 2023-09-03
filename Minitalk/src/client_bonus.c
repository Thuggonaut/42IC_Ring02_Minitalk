/*
MAKE NOTES:

1. UNICODE CHARACTERS ARE PRINTED FOR BOTH MANDATORY AND BONUS IS DUE TO THE BITS

2. ACKNOWLEDGEMENT OF RECIEPT IS SENT PER SIGNAL. A "MESSAGE" IS EQUIVALENT TO ONE SIGNAL. A '\0' IS REPRESENTED BY ONE SIGNAL
*/

#include "../inc/minitalk_bonus.h"

static void	sig_confirm(int sig) //Define a static function that takes in an integer representing a signal, and acknowledges reciept upon receiving it
{
	if (sig == SIGUSR1)
		ft_printf("Message received\n");
	else
		ft_printf("Message received\n");
}

void	send_bits(pid_t pid, char c) 
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0) 
			kill(pid, SIGUSR1); 
		else
			kill(pid, SIGUSR2); 
		usleep(100); 
		bit++; 
	}
}

int	main(int argc, char **argv) 
{
	pid_t	pid; 
	char	*msg;

	if (argc == 3) 
	{
		pid = ft_atoi(argv[1]); 
		msg = argv[2];
		while (*msg != '\0') 
		{
			signal(SIGUSR1, sig_confirm); //Each time a signal is received, acknowledge reciept
			signal(SIGUSR2, sig_confirm);
			send_bits(pid, *msg); 
			msg++; 
		}
		send_bits(pid, '\n');
	}
	else
	{
		ft_printf("Error: wrong format\n"); 
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1); 
	}
	return (0); 
}

/*
#1	Character Encoding:
		- Unicode characters can be encoded using various formats such as UTF-8, UTF-16, and UTF-32. 
			- Each of these encodings uses a different number of bytes to represent characters. 
			- UTF-8, for example, uses 1 to 4 bytes to encode characters. 
		- Using an `int *` allows you to handle these various encodings without worrying about truncating characters or losing 
		  information.
		- Using a `char *`, risks runing into limitations when dealing with characters that require more than one byte.
*/