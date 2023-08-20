#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void	sig_handler(int signal) //Define a function to handle signals recieved by the server. It will accumulate bits from received signals, effectively converting the signal patterns into characters
{
	static int	bit; //Used as a counter and to keep track of the position of the current bit being processed. Re Static variables, see #1
	static int	i; //Used to accumulate the bits received from signals to construct a character

	if (signal == SIGUSR1)
		i |= (0x01 << bit); //Set the corresponding bit of the character it is building. It does this by shifting `1` to the left by `bit` places and then performing a bitwise `|` operation with the character
	bit++;
	if (bit == 8) //Check if 8 signals have been received (i.e., a full character has been built)
	{
		ft_printf("%c", i); //If a full character has been built, print the character
		bit = 0; //Reset the bit counter and the character
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./server\n");
	}
	pid = getpid(); //Gets the PID of the server
	ft_printf("PID: %d\n", pid); //Prints its PID
	ft_printf("Waiting for a message...\n");
	while (argc == 1) //Enters an infinite loop where it waits for signals
	{
		signal(SIGUSR1, sig_handler); //sets the signal handler for SIGUSR1 and SIGUSR2 signals
		signal(SIGUSR2, sig_handler); 
		pause (); //Pauses the process until a signal is received
	}
	return (0); //If the wrong number of arguments are provided, it prints an error message and returns 0
}

/*
#1	Static variables are used to ensure consistent behavior and state preservation across different calls to the signal handler, even in situations 
	where signal handling might introduce interruptions and concurrency concerns.
		- Here's a representation of how `bit` changes across multiple calls:

			Call 1: bit = 1
			Call 2: bit = 2
			Call 3: bit = 3
			...
			Call 7: bit = 7
			Call 8: bit = 8 (Process Accumulated Bits)
			Call 9: bit = 0
			Call 10: bit = 1
			...

		- In each call to the `sig_handler` function, the `bit` value retains its state, thanks to it being static.

	For character 'A' (01000001):

	bit = 0:

	(0x01 << 0) results in 00000001.
	Since the bit at position 0 in the binary representation of 'A' is 1, the condition (signal == SIGUSR1) is true.
	The bitwise OR operation i |= (0x01 << bit) combines the value of i with 00000001, setting the first bit of i to 1.
	i becomes 00000001.
	bit = 1:

	(0x01 << 1) results in 00000010.
	Since the bit at position 1 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 00000001.
	bit = 2:

	(0x01 << 2) results in 00000100.
	Since the bit at position 2 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 00000001.
	bit = 3:

	(0x01 << 3) results in 00001000.
	Since the bit at position 3 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 00000001.
	bit = 4:

	(0x01 << 4) results in 00010000.
	Since the bit at position 4 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 00000001.
	bit = 5:

	(0x01 << 5) results in 00100000.
	Since the bit at position 5 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 00000001.
	bit = 6:

	(0x01 << 6) results in 01000000.
	Since the bit at position 6 in the binary representation of 'A' is 1, the condition (signal == SIGUSR1) is true.
	The bitwise OR operation i |= (0x01 << bit) combines the value of i with 01000000, setting the sixth bit of i to 1.
	i becomes 01000001.
	bit = 7:

	(0x01 << 7) results in 10000000.
	Since the bit at position 7 in the binary representation of 'A' is 0, the condition (signal == SIGUSR1) is false.
	The value of i remains unchanged at 01000001.
	After going through the process, the value of i becomes 01000001, which is the correct binary representation of the character 'A'. The condition 
	(signal == SIGUSR1) selectively accumulates bits based on whether the received signal is SIGUSR1.

*/