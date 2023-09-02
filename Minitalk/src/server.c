#include "../inc/minitalk.h"

void	sig_handler(int sig) //Define a function to handle signals recieved by the server. It will accumulate bits from received signals, effectively converting the signal patterns into characters
{
	static int	bit; //Used as a counter and to keep track of the position of the current bit being processed. Re Static variables, see #1
	static int	i; //Used to accumulate the bits received from signals to construct a character

	if (sig == SIGUSR1) //Check if the current received signal is `SIGUSR1` indicating that the bit is set to `1`. If so, set `i`'s corresponding bit to `1`, else `SIGUSR2` is ignored
		i |= (0x01 << bit); //It does this by shifting `1` of `00000001` to the left by `bit` places and then performing a bitwise `|` operation, effectively setting the bit's position to `1`. See #2
	bit++; //Move to the next bit of the character for processing
	if (bit == 8) //Check if 8 signals have been received (i.e., a full character has been built)
	{
		ft_printf("%c", i); //If a full character has been built, print the character
		bit = 0; //Reset the bit counter to process the next character's bits
		i = 0; //`i` is reset to `0` to start accumulating bits for the next character
	}
}

int	main(int argc, char **argv) 
{
	pid_t	pid; //Declare a process ID data type to store a process ID, to identify the server and interact with specific processes

	(void)argv; //Suppress the "unused parameter" warning for the `argv` parameter. Since `argv` is not used in this code. See #3
	if (argc != 1) //Check for the correct number of command-line arguments. If it's not equal to `1`, print an error message and instruction
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./server\n");
	}
	pid = getpid(); //Gets the PID of the server 
	ft_printf("PID: %d\n", pid); //Prints its PID
	ft_printf("Waiting for a message...\n");
	while (argc == 1) //Enters an infinite loop where it waits for signals. See #4
	{
		signal(SIGUSR1, sig_handler); //Handle the relevant signal
		signal(SIGUSR2, sig_handler); 
		pause(); //Suspend the execution of the program until a signal is received
	}
	return (0); //If the wrong number of arguments are provided, it prints an error message and returns `0`
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

#2	For example, character 'A' (01000001):

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


#3	UNUSED PARAMETERS:

	When you're required to define a function according to a certain interface, but the specific functionality of your function doesn't require all the 
	provided parameters, compiling your code might give a warning called "unused parameter." 
		- This warning is generated because the compiler notices that you've declared a parameter but never actually used it within the function.
		- Here's where (void)argv; comes into play.

	You're telling the compiler that you're aware of the parameter argv, but you intentionally don't intend to use it in the function.
		- The (void) syntax is used to cast the value argv to the type void. 
		- This is done to ensure that the compiler doesn't consider the variable as unused and generates the "unused parameter" warning.


#4	Without the while loop, the server will only process one set of signals and then exit. 
		- However, we need to process multiple messages or signals, and the while loop ensures continuous signal processing.
	
	In this code, the while loop serves as the primary mechanism for the server to continuously wait for incoming signals 
	(SIGUSR1 and SIGUSR2):
		- In essence, the purpose of this loop is to keep the server in a continuous waiting state, ready to respond to incoming signals. 
		- It sets up signal handling for both SIGUSR1 and SIGUSR2, and then suspends the execution of the program using pause(). 
		- The server remains in this suspended state until it receives a signal. 
		- When a signal is received, the sig_handler function is called to process the signal. 
		- After processing the signal, the program goes back to the pause() state to await the next signal.
*/ 