#include "../inc/minitalk_bonus.h"

void	sig_handler(int sig, siginfo_t *info, void *context) //Define a function as a signal handler that recieves and interprets signals from the server. See #1. This is part of the `struct sigaction`'s prototype. See #3
{
	static int	bit; 
	static int	i;

	(void)context; //Although unused in this specific implementation, these parameters are required by the function signature due to the way signal handlers work
	if (sig == SIGUSR1)
		i |= (0x01 << bit); 
	bit++;
	if (bit == 8) 
	{
		ft_printf("%c", i); 
		bit = 0; 
		i = 0;
		kill(info->si_pid, SIGUSR2); //Send a `SIGUSR2` signal back to the client to confirm that the character has been received. See #2. The `SA_SIGINFO` flag sends `si_pid` additional information (info->si_pid)
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	sig; //Declare a `struct sigaction` structure that will be used to configure the signal handling behavior for the server. See #3

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: wrong format\n");
		ft_printf("Try: ./server\n");
	}
	pid = getpid();
	ft_printf("PID: %d\n", pid); 
	ft_printf("Waiting for a message...\n"); 
	sig.sa_sigaction = sig_handler; //Configure the sigaction struct to handle signals upon receiving. It sets `sig_handler` as the signal handler. See #3
	sigemptyset(&sig.sa_mask); //Empty/clear the signal mask. See #4
	sig.sa_flags = SA_SIGINFO; //Enable `sig_handler()` to receive additional information about the signal, in order to send a confirmation signal back to the sender with the sender's process ID (si_pid). 
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sig, NULL); //Set up the signal handlers for SIGUSR1 and SIGUSR2 signals, in this case, both are handled the same. `&sig` refers to the `struct sigaction` `sig` that was earlier configured
		sigaction(SIGUSR2, &sig, NULL); //`NULL` indicates we're not requesting information on, or modifying the previous configuration
		pause(); 
	}
	return (0); //If the wrong number of arguments are provided, it prints an error message and returns `0`
}

/*
#1	This signature is specific to signal handler functions that are used to handle signals in a more advanced manner, allowing you to gather additional 
	information about the signal and its source:

		- `sig_handler`: 
		  This is the name of the function, which is user-defined. It's the function that will be called when the specified signal is received.

		- `int sig`: 
		  This parameter represents the signal number that triggered the handler. 
		  For example, it could be `SIGUSR1` or `SIGUSR2`. 
		  The specific signal that triggered the handler can be determined by checking the value of this parameter.

		- `siginfo_t *info`: 
		  This is a pointer to a `siginfo_t` structure. 
		  The `siginfo_t` structure holds information about a received signal, including details about the sender of the signal.
		  It includes fields such as 
		  	- `si_pid` (the process ID of the sender), 
			- `si_uid` (the user ID of the sender), and more. 
		  	- This information can be used to identify the source of the signal and make decisions based on it.

		- `void *context`: 
		  This is a generic pointer to additional context information associated with the signal. 
		  In many cases, this parameter is not used in the handler function, and you can safely ignore it. 
		  It's included to match the prototype of a signal handler function.


#2	Let's break this line down:

		- `kill`: 
		  This is a system call used to send signals to processes. 
		  It allows one process to send signals to another process.

		- `info->si_pid`: 
		  `info->si_pid` is using the -> arrow operator to access the member variable `si_pid` within the `siginfo_t` structure that info points to. 
		  In this case, `si_pid` represents the process ID of the sender of the signal.

		- `SIGUSR2`: 
		  This is the signal that is being sent back to the server. 
		  In this case, `SIGUSR2` is used as an acknowledgment signal. 
		  When the client successfully receives a byte and assembles it, it sends this acknowledgment signal back to the server to let it know that the 
		  byte was received correctly.

	When this line is executed, it sends a `SIGUSR2` signal to the process (server) with the process ID stored in `info->si_pid`. 
		- The server is programmed to handle this signal as part of its signal handling mechanism. 
		- When the server receives the `SIGUSR2` signal, it knows that the corresponding byte was received by the client and successfully processed. 
		- This forms the basis of the acknowledgment mechanism, ensuring reliable communication between the client and server.

	Why is SIGUSR2 being used?
		- While you could use either SIGUSR1 or SIGUSR2 for confirmation, there are a few considerations that might lead to choosing one over the other:
			- Since SIGUSR1 and SIGUSR2 are custom signals without predefined meanings, SIGUSR2 is chosen in this case to explicitly convey the
			  acknowledgment because SIGUSR1 is already used for other purposes in our code. 
			- Using different signals for different purposes can help make the code more readable. 


#3	The `struct sigaction` is a structure used to specify and control the action taken when a specific signal is received. 
		- It provides a more flexible and powerful way to handle signals compared to the older signal() function. 
		- The prototype of `struct sigaction` is:

		  	struct sigaction 
		  	{
    			void (*sa_handler)(int);
    			void (*sa_sigaction)(int, siginfo_t *, void *);
    			sigset_t sa_mask;
    			int sa_flags;
    			void (*sa_restorer)(void);
			}

		- `sa_handler`: 
		  This is a function pointer that specifies the handler function to be called when the signal is received. 
		  The function should have the following prototype: 
			- `void handler_function(int signum);`. 
			- Our code does not use this member.

		- `sa_sigaction`: 
		  This is a function pointer that specifies the alternate handler function to be called when the signal is received. 
		  It provides additional information about the signal and its source. 
		  The function should have the following prototype: 
		  	- `void sigaction_function(int signum, siginfo_t *info, void *context);`. 
			- Our code uses this member.

		- `sa_mask`: 
		  This member specifies the set of signals that should be blocked (masked) while the handler function is executing. 
		  It prevents other signals from interrupting the handler's execution.

		- `sa_flags`: 
		  This member is used to specify various flags that control the behavior of signal handling. 
		  Some commonly used flags include:

			- `SA_RESTART`: 
			  Restart system calls interrupted by the signal.
			- `SA_SIGINFO`: 
			  Use the sa_sigaction member instead of sa_handler.
			- `SA_NOCLDSTOP`: 
			  Do not generate SIGCHLD when child processes stop.
			- `sa_restorer`: 
			  This member specifies an optional pointer to a function that will be called after the signal handler returns. 
			  It's used for internal purposes and is not commonly used in user code.

		- To use struct sigaction, you typically follow these steps:
			- Declare a `struct sigaction` variable.
			- Configure the members of the struct, including the handler function, signal mask, and flags.
			- Use the `sigaction()` function to apply the configuration to the desired signal.


#4	`sigemptyset(&sig.sa_mask);` initializes an empty signal set for the `sa_mask` member of the `sig` struct. 
		- The `sa_mask` member specifies a set of signals that should be blocked (masked) while the signal handler (sa_sigaction) is 
		  executing. 
		- By using `sigemptyset()`, we ensure that no signals are blocked during the execution of the signal handler. 
		- This is important to avoid potential signal conflicts or unintended behavior.
		- While `sa_mask` is not explicitly used to block signals in this specific code, the use of `sigemptyset(&sig.sa_mask);` 
		  practices good coding defenses by ensuring that the signal handler operates with a clean slate and without unintended signal
		  masking.
*/