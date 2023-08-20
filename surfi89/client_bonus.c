#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

static void	sig_confirm(int signal) //This function is a signal handler that is called when the client receives a SIGUSR1 or SIGUSR2 signal. It prints a confirmation message depending on the signal received
{
	if (signal == SIGUSR1)
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
	else
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
}

void	send_bits(pid_t pid, char c) //sends the bits of a character to the server
{
	int	bit; //used as a counter

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0) //checks if the current bit of the character is 1. It does this by shifting 1 to the left by bit places and then performing a bitwise AND operation with the character. If the result is not 0, it means the bit is 1
			kill(pid, SIGUSR1); //If the bit is 1, it sends the SIGUSR1 signal to the server
		else
			kill(pid, SIGUSR2); //If the bit is 0, it sends the SIGUSR2 signal to the server
		usleep(100); //makes the process sleep for 100 microseconds. This is done to ensure that the server has enough time to handle the signal before the next one is sent
		bit++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*msg;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]); //Converts the first argument to an integer to get the PID of the server
		msg = argv[2];
		while (*msg != '\0') //Iterates over each character of the second argument (the message)
		{
			signal(SIGUSR1, sig_confirm); //sets the signal handler for SIGUSR1 and SIGUSR2 signals
			signal(SIGUSR2, sig_confirm);
			send_bits(pid, *msg); //Sends each character of the message to the server
			msg++;
		}
		send_bits(pid, '\n'); //Sends a newline character to signify the end of the message
	}
	else
	{
		ft_printf("Error: wrong format \n"); //If the wrong number of arguments are provided, print an error message
		ft_printf("Try: ./client <PID> <MESSAGE> \n");
		return (1); //Indicate error
	}
	return (0); //Indicate success
}