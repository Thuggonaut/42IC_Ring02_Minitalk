#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	ft_handler(int signal) //This function is the signal handler for the server. It is called whenever the server receives a SIGUSR1 or SIGUSR2 signal
{
	static int	bit; //used as a counter
	static int	i;

	if (signal == SIGUSR1)
		i |= (0x01 << bit); //sets the corresponding bit of the character it is building. It does this by shifting 1 to the left by bit places and then performing a bitwise OR operation with the character
	bit++;
	if (bit == 8) //Checks if 8 signals have been received (i.e., a full character has been built)
	{
		ft_printf("%c", i); //If a full character has been built, it prints the character
		bit = 0; //Resets the bit counter and the character
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid(); //Gets the PID of the server
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid); //Prints its PID
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	while (argc == 1) //Enters an infinite loop where it waits for signals
	{
		signal(SIGUSR1, ft_handler); //sets the signal handler for SIGUSR1 and SIGUSR2 signals
		signal(SIGUSR2, ft_handler); 
		pause (); //Pauses the process until a signal is received
	}
	return (0); //If the wrong number of arguments are provided, it prints an error message and returns 0
}