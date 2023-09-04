#include "../inc/minitalk.h"

void	send_bits(pid_t pid, char c) //Define a function that transmits the binary representation of the character's bits, to the server corresponding to the process ID, using signals
{
	int	bit; //Used as a counter and to iterate through the individual bits of the character `c`

	bit = 0;
	while (bit < 8) //Iterate through each of the 8 bits in the character `c`. A char data type consists of 8 bits
	{
		if ((c & (0x01 << bit)) != 0) //Check if the current bit of the character is `1`. It does this by shifting `1` to the left by bit places and then performing a bitwise `&` operation with the character. If the result is not `0`, it means the bit is `1`. See #1
			kill(pid, SIGUSR1); //If the bit is `1`, it sends the `SIGUSR1` signal to the server
		else
			kill(pid, SIGUSR2); //If the bit is 0, it sends the `SIGUSR2` signal to the server
		usleep(100); //Make the process sleep for 100 microseconds. This is done to ensure that the server has enough time to handle the signal before the next one is sent. See #2
		bit++; //Move to the next bit for processing
	}
}

int	main(int argc, char **argv) //`argv` is a pointer to an array of strings. By using a double pointer `char **argv`, the program can access and retrieve each individual argument as a null-terminated string
{
	pid_t	pid; //Declare a process ID data type to store a process ID, to identify the server and interact with specific processes
	char	*msg; //Declare a pointer to the string and message

	if (argc == 3) //Perform operations only if argc is `3`, meaning there should be `2` arguments in addition to the program name 
	{
		pid = ft_atoi(argv[1]); //Converts the first argument to an integer to get the PID of the server
		msg = argv[2]; //Assign to `msg` the second argument
		while (*msg != '\0') //Iterate over each character of the string (the message and second argument)
		{
			send_bits(pid, *msg); //Send the current character of the string to the server corresponding to the process ID
			msg++; //Move to the next character for processing
		}
		send_bits(pid, '\n'); //Send a newline character to signify the end of the string and message
	}
	else
	{
		ft_printf("Error: wrong format\n"); //If the wrong number of arguments are provided, print an error message
		ft_printf("Try: ./client <PID> <MESSAGE>\n");
		return (1); //Indicate error
	}
	return (0); //Indicate success
}

/*
#1	`0x01` is a hexadecimal (base-16) representation of an integer value. 
		- In binary, `0x01` is equivalent to `0000 0001`
		- Using the `&` bitwise operator essentially compares the binary representation of `c` to `0000 0001` and checks if the current bit of `c` is 
		  a `1` if both bits are `1` (meaning it is set/switched on) or `0` if either bit is `0`. 
		- In order to iterate through each bit of `c`, we use the `<<` bitwise operator to shift left `0000 0001` by `bit` number of bits, starting from `0` which
		  is the least significant bit (LSB).
	
	Say we have, c = 'A' which is ASCII 65, which is 0100 0001 in binary:

	1st iteration:		0100 0001
					&	0000 0001	= 1

	2nd iteration:		0100 0001
					&	0000 0010	= 0	

	3rd iteration:		0100 0001
					&	0000 0100	= 0

	4th iteration:		0100 0001
					&	0000 1000	= 0
	
	5th iteration:		0100 0001
					&	0001 0000	= 0

	6th iteration:		0100 0001
					&	0010 0000	= 0

	7th iteration:		0100 0001
					&	0100 0000	= 1

	8th iteration:		0100 0001
					&	1000 0000	= 0


#2	The `100` microseconds value is not arbitrary.
		- `100` microseconds have been chosen based on testing with the system's characteristics. 
		- It's a balance between providing the server enough time to process signals and minimizing the delay in transmitting the entire message. 
		- In practice, we might need to adjust this value based on the system's behavior and performance characteristics. 
		- We can experiment with different values to determine the optimal delay that allows reliable signal processing without introducing unnecessary 
		  overhead.
*/