#include "../inc/minitalk_bonus.h"

static void	sig_confirm(int sig) //Define a static function that takes in an integer representing a signal, and acknowledges reciept upon receiving it
{
	if (sig == SIGUSR1)
		ft_printf("Message received\n");
	else //If SIGUSR2
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
			signal(SIGUSR1, sig_confirm); //Each time a signal is received, it is the server acknowledging reciept
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
BONUS PART:
- Both the client and server supports Unicode characters. 
- The server sends the client acknowledgement of receipt upon receving the message.

Character Encoding:
- Actually, our mandatory executables as well as our bonus executables can both handle Unicode characters. 
- What makes this possible is our use of binary encoding and decoding.

Here's how:

1.	Sending Characters: 
	- The `send_bits` function in our client codes sends characters bit by bit. 
	- It doesn't care about the specific character set, whether it's ASCII or Unicode. 
	- It merely sends the binary representation of each character. 
	- Unicode characters are represented in binary form just like ASCII characters, typically using more than 1 byte (8 bits), but the `send_bits` 
	  function doesn't differentiate. 
	- It sends the individual bits of the character one by one using the same signals (SIGUSR1 and SIGUSR2).

2.	Receiving Characters: 
	- The `sig_handler` function in our server code accumulates bits received through signals and interprets them as characters.
	- Again, it doesn't distinguish between ASCII and Unicode characters. 
	- It accumulates 8 bits and interprets them as a character. 

3. 	In essence, our code is binary-agnostic. 
	- It doesn't interpret characters based on their specific encoding (like UTF-8), but rather it interprets them based on their binary 
	  representation. 
	- This allows it to handle a wide range of characters, including Unicode, as long as they can be represented within a single byte (8 bits).


Message acknowledgment:
- Note, that each signal sent/recieved represents a "message". 
- Recall, if the client sends a message that has n numbers of characters, the server will send back to the client n numbers of acknowledgements,
  plus 1 that represents the '\0' character which indicates the end of a string/message.
*/