# Minitalk:

The purpose of this project is to code a small data change program using UNIX signals.


## Preface:
- While this project has the reputation of being "easy", it was intimidating to me. The concept of "signals" was so foreign and it took me some time to understand it, but we got there. 
- What gave me the :lightbulb moment, was the metaphor of using the SIGUSR1 and SIGUSR2 signals to communicate between the clients and servers like you would with Morse code.
- We will be completing both the [Mandatory] and [Bonus] parts. Here is the outline:
	- Step 1: [Learn UNIX signals]
	- Step 2: [Understand SIGUSR1 and SIGUSR2 signals]
	- Step 3: [Learn the functions permitted for use]
	- Step 4: [Understand the Minitalk assignment and concepts]
	- Step 5: [Write the structure of directories and files]
	- Step 6: [Code Minitalk]
	- Step 7: [Test Minitalk]
	- Step 8: [Evaluation checklist]


## The Mandatory Part:

1. You must create a communication program in the form of a `client` and a `server`.
    • The server must be started first. After its launch, it has to print its `PID`.
    • The client takes two parameters: 
        ◦ The server PID.
        ◦ The string to send.

2. The client must send the string passed as a parameter to the server.

3. Once the string has been received, the server must print it.
    • The server has to display the string pretty quickly.
    • Your server should be able to receive strings from several clients in a row without needing to restart.
    • The communication between your client and your server has to be done only using UNIX signals.
    • You can only use these two signals: SIGUSR1 and SIGUSR2. 
	• 1 second for displaying 100 characters is way too much!


## The Bonus Part:

1. The server acknowledges every message received by sending back a signal to the client.
2. Unicode characters are supported by both the client and server.


## Step 1: Learn UNIX signals

#### UNIX SIGNALS:

- In Unix-like operating systems, signals are a form of inter-process communication (IPC) used to notify a process that a particular event has occurred. 
- Signals can be generated by the operating system or sent by one process to another. 
- They are used for various purposes, including process management, error handling, and communication between processes. 
- Signals can only transmit one bit at a time.
    - The limitation of transmitting only one bit at a time through signals is intentional with the purpose of being lightweight, efficient, and suitable for real-time event notification and simple inter-process communication.
    - While signals are suitable for lightweight communication and event notification, they are not the most efficient way to transmit large amounts of data between processes. For more data-intensive communication, other mechanisms like sockets, pipes, shared memory, and message queues are often used.

Here's a basic overview of how signals work and how you can use them in a client-server program:

Signal Basics:
- Signals are represented by integer values, such as 
    - SIGINT (2), 
    - SIGTERM (15), 
    - SIGUSR1 (10), and so on.
- The kill system call is commonly used to send signals to processes. 
    - The command kill -<signal> <pid> sends a signal to the specified process.


Handling Signals:
- In C, you can set up signal handlers using the signal() function or the more modern sigaction() function.
- A signal handler is a function that gets called when a specific signal is received. 
    - It allows your program to react to the signal.


Signal Handling in a Client-Server Program:
- In your client-server program, you can use signals to facilitate communication between the client and server processes. 
    - For instance, you could define a custom signal to indicate when the client wants to communicate with the server.


Here's a simple example of a client-server program using signals in C:
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void server_signal_handler(int signum) 
{
    // Handle server-specific signal
    if (signum == SIGUSR1) 
    {
        printf("Server received a signal from the client.\n");
    }
}

int main() 
{
    // Set up server signal handler
    signal(SIGUSR1, server_signal_handler);

    // Fork a child process for the client
    pid_t client_pid = fork();

    if (client_pid == 0) 
    {
        // This is the client process
        printf("Client process is running.\n");
        // Send a signal to the server process
        kill(getppid(), SIGUSR1);
    } 
    else if (client_pid > 0) 
    {
        // This is the server process
        printf("Server process is running.\n");
        // Wait for the signal from the client
        pause();
    } 
    else 
    {
        perror("fork");
        exit(1);
    }
    return (0);
}
```