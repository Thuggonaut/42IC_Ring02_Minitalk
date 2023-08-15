#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	ft_handler(int signal, siginfo_t *info, void *s) //This function is a signal handler that is called when the server receives a SIGUSR1 or SIGUSR2 signal. It is defined with the sigaction function, which allows for more advanced signal handling
{
	static int	bit;
	static int	i;

	(void)info;
	(void)s;
	if (signal == SIGUSR1)
		i |= (0x01 << bit); //If the signal is SIGUSR1, it sets the corresponding bit of the character it is building. It does this by shifting 1 to the left by bit places and then performing a bitwise OR operation with the character
	bit++;
	if (bit == 8) //Checks if 8 signals have been received (i.e., a full character has been built)
	{
		ft_printf("%c", i); //If a full character has been built, it prints the character
		bit = 0; //Resets the bit counter and the character
		i = 0;
		kill(info->si_pid, SIGUSR2); // Sends a SIGUSR2 signal back to the client to confirm that the character has been received
	}
}

int	main(int argc, char **argv)
{
	pid_t					pid;
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid); //Gets the PID of the server
	ft_printf("\033[90mWaiting for a message...\033[0m\n"); //Prints the PID of the server
	sig.sa_sigaction = ft_handler; //Sets up the sigaction struct to handle signals. It sets ft_handler as the signal handler
	sigemptyset(&sig.sa_mask); //empties the signal mask, and sets the flags to 0
	sig.sa_flags = 0;
	while (argc == 1) //Enters an infinite loop where it waits for signals
	{
		sigaction(SIGUSR1, &sig, NULL); // Sets up the signal handlers for SIGUSR1 and SIGUSR2 signals
		sigaction(SIGUSR2, &sig, NULL);
		pause (); //Pauses the process until a signal is received
	}
	return (0); //If the wrong number of arguments are provided, it prints an error message and returns 0
}