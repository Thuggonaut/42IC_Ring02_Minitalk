#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	ft_send_bits(pid_t pid, char i) //sends the bits of a character to the server
{
	int	bit; //used as a counter

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0) //checks if the current bit of the character is 1. It does this by shifting 1 to the left by bit places and then performing a bitwise AND operation with the character. If the result is not 0, it means the bit is 1
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
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]); //Converts the first argument to an integer to get the PID of the server
		while (argv[2][i] != '\0') //Iterates over each character of the second argument (the message
		{
			ft_send_bits(pid, argv[2][i]); //Sends each character of the message to the serve
			i++;
		}
		ft_send_bits(pid, '\n'); //Sends a newline character to signify the end of the message
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n"); //If the wrong number of arguments are provided, it prints an error message and returns 1
		ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}