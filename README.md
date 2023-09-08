# ☎️ Minitalk:

The purpose of this project is to code a small data exchange program using UNIX signals.


## 🔷 Preface:
- While this project has the reputation of being "easy", it was intimidating to me. The concept of "signals" was so foreign and it took me some time to understand it, but we got there. 
- What gave me the 💡 moment, was the metaphor of using the SIGUSR1 and SIGUSR2 signals to communicate between the clients and servers like you would with Morse code.
- Keep an eye out for the **"🔑Key"** words, that will imply significance for coding our program.
- We will be completing both the [Mandatory](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-the-mandatory-part) and [Bonus](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-the-bonus-part) parts. Here is the outline:
	- Step 1: [Learn UNIX signals](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-1-learn-unix-signals)
	- Step 2: [Understand SIGUSR1 and SIGUSR2 signals](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-2-understand-sigusr1-and-sigusr2-signals)
	- Step 3: [Learn the functions permitted for use](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-3-learn-the-functions-permitted-for-use)
	- Step 4: [Understand the Minitalk assignment and concepts](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-4-understand-the-minitalk-assignment-and-concepts)
	- Step 5: [Write the structure of directories and files](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-5-write-the-structure-of-directories-and-files)
	- Step 6: [Code Minitalk](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-6-code-minitalk)
	- Step 7: [Test Minitalk](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-7-test-minitalk)
	- Step 8: [Evaluation checklist](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-step-8-evaluation-checklist)


## 🔷 The Mandatory Part:

1. We must create a communication program in the form of a `client` and a `server`.
    - The server must be started first. After its launch, it has to print its `PID`.
    - The client takes two parameters: 
        - The server PID.
        - The string to send.

2. The client must send the string passed as a parameter to the server.

3. Once the string has been received, the server must print it.
    - The server has to display the string pretty quickly.
    - our server should be able to receive strings from several clients in a row without needing to restart.
    - The communication between our client and our server has to be done only using UNIX signals.
    - we can only use these two signals: SIGUSR1 and SIGUSR2. 
	- 1 second for displaying 100 characters is way too much!


## 🔷 The Bonus Part:

1. The server acknowledges every message received by sending back a signal to the client.
2. Unicode characters are supported by both the client and server.


## 🔷 Step 1: Learn UNIX signals

🔹 **UNIX Signals:**

- In Unix-like operating systems, signals are a form of inter-process communication (IPC) used to notify a process that a particular event has occurred. 
- Signals can be generated by the operating system or sent by one process to another. 
- They are used for various purposes, including process management, error handling, and communication between processes. 
- **🔑Key: Signals can only transmit one bit at a time.**
    - The limitation of transmitting only one bit at a time through signals is intentional with the purpose of being lightweight, efficient, and suitable for real-time event notification and simple inter-process communication.
    - While signals are suitable for lightweight communication and event notification, they are not the most efficient way to transmit large amounts of data between processes. For more data-intensive communication, other mechanisms like sockets, pipes, shared memory, and message queues are often used.

Here's a basic overview of how signals work and how we can use them in a client-server program:

🔹 **Signal Basics:**
- Signals are represented by integer values, such as 
    - SIGUSR1 (10)
    - SIGUSR2 (12)
    - SIGINT (2)
    - SIGTERM (15), and so on. 

🔹 **Signal Handling in a Client-Server Program:**
- In C, we can set up signal handlers using the signal() function or the more sophisticated sigaction() function.
- A signal handler is a function that gets called when a signal is received. 
    - It allows our program to react/respond to the signal.
- In our client-server program, we can use signals to facilitate communication between the client and server processes. 
    - For instance, we could define a custom signal to indicate how the client wants to communicate with the server.

- Here's a simple example of a client-server program using signals in C:
    ```
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <signal.h>

    void signal_handler(int signum) 
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
        signal(SIGUSR1, signal_handler);

        // Prompt user to run the client in a separate terminal or background
        printf("Server process is running.\n");
        printf("Please run the client process separately and send it a SIGUSR1 signal.\n");
        pause(); // Wait for the signal from the client

        return (0);
    }
    ```

## 🔷 Step 2: Understand SIGUSR1 and SIGUSR2 signals
Only SIGUSR1 and SIGUSR2 signals are permitted for use.

- **🔑Key: SIGUSR1 and SIGUSR2 are user-defined signals.**
- These signals are provided for application-specific purposes and are not assigned specific meanings by the operating system itself. Instead, they are available for programmers to use as needed to implement custom behavior or communication between processes. 
    - For intstance, they can be used to trigger custom actions in a program when specific events occur.
- Both `SIGUSR1 User-defined Signal 1` and `SIGUSR2 User-defined Signal 2` provide a way for applications to communicate with their processes in a customized manner. 
- When sending or receiving these signals, you can use the kill system call or the kill command in the terminal, passing the appropriate signal number and the process ID (PID) of the target process.


## 🔷 Step 3: Learn the functions permitted for use

1. [signal](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-1-signal)
2. [sigemptyset](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-2-sigemptyset)
3. [sigaddset](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-3-sigaddset)
4. [sigaction](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-4-sigaction)
5. [kill](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-5-kill)
6. [getpid](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-6-getpid)
7. [pause](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-7-pause)
8. [sleep](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-8-sleep)
9. [usleep](https://github.com/Thuggonaut/42IC_Ring02_Minitalk/blob/main/README.md#-9-usleep)

#### 🔸 **1. signal():**
- is a function in C that specifies how a signal should be handled. 

- Syntax:
    ```
    #include <signal.h>

    void (*signal(int signum, void (*handler)(int)))(int);
    ```

- Parameters:
    - `int signum`: 
        - This is the signal number for which you want to specify a handler function. 
        - Recall, signals are represented by unique integers.

    - `void (*handler)(int)`: 
        - This parameter is a pointer to a function that will be called when the specified signal is received. 
        - The function should take an integer parameter, which represents the signal number.

- Return Value:
    - The signal() function returns a pointer to the previous signal handler function for the specified signal. 
    - This allows you to save the previous handler if you need to restore it later. If there was no previous handler, it returns `SIG_ERR`.

- Usage:
    - **🔑Key: The signal() function is used to specify how a program should respond when a particular signal is received.**
    - You provide it with the signal number (signum) and a pointer to the function (handler) that should be executed when that signal is received.

- Example:
    ```
    #include <stdio.h>
    #include <signal.h>
    #include <stdlib.h>

    // Custom signal handler function for SIGUSR1
    void sigusr1_handler(int signum) 
    {
        printf("Received SIGUSR1 signal (%d)\n", signum);
    }

    // Custom signal handler function for SIGUSR2
    void sigusr2_handler(int signum) 
    {
        printf("Received SIGUSR2 signal (%d)\n", signum);
    }

    int main() 
    {
        // Set custom signal handlers
        signal(SIGUSR1, sigusr1_handler);
        signal(SIGUSR2, sigusr2_handler);

        printf("Waiting for signals...\n");

        // Keep the program running
        while (1) 
        {
            // Sleep to keep the program alive
            sleep(1);
        }
        return (0);
    }
    ```

#### 🔸 **2. sigemptyset():**
- is a function in C that is used to initialize an empty signal set. 
- The purpose of sigemptyset() is to create an empty set of signals, which can then be manipulated using other signal-related functions.

- Syntax:
    ```
    #include <signal.h>

    int sigemptyset(sigset_t *set);
    ```

- Parameters:
    - `set`: 
        - A pointer to a sigset_t data structure that will be initialized as an empty signal set.

- Return Value:
    - The function returns 0 on success and -1 on error and sets errno to show that an error has occurred.

- Usage:
    - The primary use of sigemptyset() is to initialize a signal set (represented by the sigset_t data structure) to an empty state. 
        - This means that after calling this function, the signal set will not contain any signals.
    - It prepares a signal set before adding or removing signals using other functions like sigaddset() and sigdelset(). 
    - Signal sets are used in various signal-related functions, such as when configuring signal masks for blocking or unblocking signals, as well as for checking the presence of signals in a set.


#### 🔸 **3. sigaddset():**
-  is a function in C used to manipulate signal sets.
-  Signal sets are data objects that let a thread keep track of groups of signals. 
    - For example, a thread might create a signal set to record which signals it is blocking, and another signal set to record which signals are pending.
- In other words, signal sets are collections of signals that are grouped together. 

- Syntax:
    ```
    #include <signal.h>

    int sigaddset(sigset_t *set, int signum);
    ```

- Parameters:
    - `sigset_t *set`: 
        - This is a pointer to the signal set wherein you want to add a new signal.

    - `int signum`: 
        - This is the signal number that you want to add to the signal set. 
        - The signals are defined in the signal.h header file as macros, they include SIGINT, SIGSTOP, SIGUSR1, etc.
        - Each signal has a specific number associated with it.

- Return Value:
    - The function returns 0 on success and -1 on error and sets errno to show that an error has occurred.

- Usage:
    - The primary use of sigaddset() is used to add a specified signal to a specified signal set. 
    - This can be useful when you want to customize how your program responds to different signals.


#### 🔸 **4. sigaction():**
- **🔑Key: for our bonus part, this function can be used to set the action that should be taken when a specific signal occurs.**
- Similarly to signal(), it is a signal handler but in a more sophisticated manner.

- Syntax:
    ```
    #include <signal.h>

    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    ```

- Parameters:
    - `signum`: 
        - This is the signal number. 
        - Each signal has a specific number associated with it, such as SIGINT for the interrupt signal.

    - `act`: 
        - This is a pointer to a struct sigaction which specifies the new action to take for the signum signal. 
        - If this parameter is NULL, then the signal's disposition is not changed, but the current disposition can still be retrieved via the oldact parameter.

    - `oldact`: 
        - This is a pointer to a struct sigaction where sigaction() saves the current action for the signum signal. 
        - If this parameter is NULL, then the current disposition is not saved.

- Return Value:
    - The function returns 0 on success and -1 on error and sets errno to show that an error has occurred.

- Usage:
    - The sigaction() function allows the calling process to change its action for the signal `signum` to the action described by `act`. 
    - `signum` specifies the signal and `act` specifies the new action to take. 
    - A NULL `act` argument can be used to query the current action without changing it.

- Example:
    ```
    #include <stdio.h>
    #include <stdlib.h>
    #include <signal.h>

    void signal_handler(int signum) 
    {
        if (signum == SIGUSR1) 
        {
            printf("Received SIGUSR1 signal.\n");
        } 
        else if (signum == SIGUSR2) 
        {
            printf("Received SIGUSR2 signal.\n");
        }
    }

    int main() 
    {
        struct sigaction sa;
        sa.sa_handler = signal_handler;
        sa.sa_flags = 0;

        if (sigaction(SIGUSR1, &sa, NULL) == -1) 
        {
            perror("Error setting up SIGUSR1 handler");
            return 1;
        }

        if (sigaction(SIGUSR2, &sa, NULL) == -1) 
        {
            perror("Error setting up SIGUSR2 handler");
            return 1;
        }

        printf("Waiting for signals...\n");
        while (1) 
        {
            // Do other tasks or simply wait here
        }
        return (0);
    }
    ```

- In this example:
    - The sigaction() function is used to associate the customHandler() function with both SIGUSR1 and SIGUSR2 signals. 
    - When these signals are received, the custom handler function is executed, providing a way to perform specific actions in response to these signals. 
    - The program then enters an infinite loop, waiting for signals while continuing its normal execution.


#### 🔸 **5. kill():**
- **🔑Key: this function is used to send a signal to a process or a group of processes specified by the process ID.**

- Syntax:
    ```
    #include <signal.h>

    int kill(pid_t pid, int sig);
    ```

- Parameters:
    - `pid`: 
        - The process ID of the target process. It can take the following values:
            - Positive PID: 
                - Sends the signal to the process with the specified PID.
            - `0`: 
                - Sends the signal to all processes in the current process group.
            - `-1`: 
                - Sends the signal to all processes for which the calling process has permission to send signals, except for itself.
            - Negative PID: 
                - Sends the signal to all processes in the process group whose ID is the absolute value of pid.
    - `int sig`: 
        - This parameter is the signal number that you want to send. 
        - It's an integer representing the specific signal you wish to use. 
        - Common signals include SIGUSR1, SIGUSR2, SIGTERM, SIGKILL, and many more. 


- Return Value:
    - The function returns 0 on success and -1 on error and sets errno to show that an error has occurred.

- Usage:
    - The kill() function is used to send a signal to a process or a group of processes specified by the pid. 
    - The sig parameter specifies the signal to be sent, which can be either a signal number or a signal constant.
    - By convention, a 0 signal is often used to check the validity of the pid without actually sending a signal.

- Example:
    ```
    #include <sys/types.h>
    #include <signal.h>

    int main() 
    {
        // Sending SIGUSR1 to process with PID 1234
        if (kill(1234, SIGUSR1) == 0) 
        {
            // Successfully sent SIGUSR1
        } else 
        {
            // Failed to send SIGUSR1
        }

        // Sending SIGUSR2 to process with PID 5678
        if (kill(5678, SIGUSR2) == 0) 
        {
            // Successfully sent SIGUSR2
        } else 
        {
            // Failed to send SIGUSR2
        }

        return (0);
    }
    ```

- In this example:
    - The program sends SIGUSR1 to process 1234 and SIGUSR2 to process 5678. 
    - These signals can be caught and handled by the receiving processes to perform specific actions or respond to events.


#### 🔸 **6. getpid():**
- **🔑Key: this function is used to retrieve the process ID (PID)** of the calling process, which is a unique identifier assigned to each running process on the system.

- Syntax:
    ```
    #include <unistd.h>

    pid_t getpid(void);
    ```

- Parameters:
    - does not take any parameters.

- Return Value:
    - The getpid() function returns the process ID (PID) of the calling process. 
    - The PID is of type pid_t, which is usually an integer.

- Usage:
    - The getpid() function is commonly used to identify a specific process or to perform process-specific operations. 
    - It allows programs to distinguish between different processes and perform actions based on their process ID.

- Example:
    ```
    #include <stdio.h>
    #include <unistd.h>

    int main(void) 
    {
        pid_t pid = getpid();
        printf("My process ID is %d.\n", pid);
        return (0);
    }
    ```

    - In this example, the getpid() function is called to retrieve the process ID of the current process. 
    - The process ID is then printed using printf().

    Output:
    ```
    My process ID is 12345.
    ```

    - Please note that the process ID is unique for each running process on the system, and it can change every time the program is executed.


#### 🔸 **7. pause():**
- function in C is used to suspend the execution of a program until a signal is received.

- Syntax:
    ```
    #include <unistd.h>

    int pause(void);
    ```

- Parameters:
    - does not take any parameters.

- Return Value:
    - The pause() function returns -1 and sets errno to EINTR if it is interrupted by a signal. 
    - Otherwise, it does not return.

- Usage:
    - **🔑Key: The pause() function is typically used in signal handling to wait for a specific signal before proceeding with further execution.** 
    - It allows a program to pause its execution until a signal handler changes the program flow.

- Example:
    ```
    #include <stdio.h>
    #include <signal.h>
    #include <unistd.h>

    void signal_handler(int signum) 
    {
        if (signum == SIGUSR1) 
        {
            printf("Received SIGUSR1 signal.\n");
            // Handle SIGUSR1 signal
        } 
        else if (signum == SIGUSR2) 
        {
            printf("Received SIGUSR2 signal.\n");
            // Handle SIGUSR2 signal
        }
    }

    int main() 
    {
        // Register signal handlers
        signal(SIGUSR1, signal_handler);
        signal(SIGUSR2, signal_handler);

        printf("My process ID: %d\n", getpid());

        // Pause the program, waiting for signals
        pause();
        return (0);
    }
    ```

    - In this example:
        - The signal_handler() function is defined to handle the SIGUSR1 and SIGUSR2 signals. 
            - It checks which signal was received and performs corresponding actions.
        - In the main() function, we register signal handlers for SIGUSR1 and SIGUSR2 using the signal() function.
        - We then print the process ID using getpid().
        - The program enters the pause() function, which will block until a signal is received. 
            - Once a signal is received, the corresponding signal_handler() function is called to handle the signal.


#### 🔸 **8. sleep():**
- function in C is used to pause the execution of a program for a specified number of seconds.
- in comparison to `usleep()`, `sleep()`` is used to pause the execution of a program for a specified number of whole seconds. It is a coarser-grained delay function.

- Syntax:
    ```
    #include <unistd.h>

    unsigned int sleep(unsigned int seconds);
    ```

- Parameters:
    - seconds: 
        - specifies the number of seconds the program should sleep.

- Return Value:
    - The sleep() function returns the number of seconds remaining if it is interrupted by a signal, or 0 if the specified time has elapsed.

- Usage:
    - The sleep() function is commonly used to introduce delays in program execution or to wait for a specific duration before proceeding with further execution.
    - It allows programs to pause for a specified amount of time, which can be useful for synchronization between processes or implementing timed behavior.


#### 🔸 **9. usleep():**
- **🔑Key: this function is used to suspend the execution of a program for a specified number of microseconds.**
- In comparison to `sleep()`, `usleep()` is used to introduce a delay in microseconds, which is a much finer-grained delay compared to sleep(). It allows you to specify delays in fractions of a second.

- Syntax:
    ```
    #include <unistd.h>

    int usleep(useconds_t useconds);
    ```

- Parameters:
    - `useconds`:
        - specifies the number of microseconds the program should sleep.

- Return Value:
    - The usleep() function returns 0 if the execution was successful (execution successfully suspended) or -1 if there was an error.

- Usage:
    - The usleep() function is commonly used to introduce delays in program execution or to pause the program for a specific duration in microseconds.
    - It provides a higher precision delay compared to the sleep() function, which operates in seconds.
    - The usleep() function is available in POSIX-compliant systems but is considered obsolete in favor of the nanosleep() function.

- Example:
    ```
    #include <stdio.h>
    #include <unistd.h>
    #include <signal.h>

    void signalHandler(int signal) 
    {
        printf("Signal %d received.\n", signal);
    }

    int main(void) 
    {
        signal(SIGUSR1, signalHandler);
        signal(SIGUSR2, signalHandler);
        printf("Waiting for signals...\n");

        // Sleep for 1 second (1000000 microseconds)
        usleep(1000000);
        
        printf("Resuming execution.\n");
        return (0);
    }
    ```

- In this example:
    - The program sets up signal handlers for the SIGUSR1 and SIGUSR2 signals.
    - It then waits for signals by using the usleep() function to pause the program for 1 second (equivalent to 1000000 microseconds).
    - After the sleep period, if any of the signals are received, the corresponding signal handler is invoked.
    - The program resumes execution and prints the "Resuming execution" message.

- Output:
    ```
    Waiting for signals...
    ^CSignal 2 received.
    Resuming execution.
    ```

    - During the 1-second sleep, if either SIGUSR1 or SIGUSR2 signals are received, the signal handler will be called, and the program will resume execution after the sleep period.


## 🔷 Step 4: Understand the Minitalk assignment and concepts

🔹 **1. What does “create a communication program in the form of a client and a server” mean?**
- To develop an application that allows communication between two separate entities: a client and a server.
- The client and server will interact with each other using SIGUSR1 and SIGUSR2 signals.

🔹 **2. What is a client?**
- A client initiates communication and sends requests.
- In the context of our assignment, the client is responsible for sending a message to the server, requesting it to process the provided string. 
- The client takes two parameters: 
    - the server's PID (Process ID) and 
    - the string to send. 
- After sending the request, the client waits for an acknowledgment from the server (Bonus part).

🔹 **3. What is a server?**
- The server should be started first and print its Process ID (PID) after launch.
- A server receives and processes client requests before sending back responses.
- In the context of our assignment, the server would be responsible for receiving messages from clients and processing the provided strings. 
- After processing, the server acknowledges the receipt by sending a signal back to the client (Bonus part). 

🔹 **4. What is a PID?**
- A Process Identifier (PID) is a unique number used to uniquely identify an active process.
- This number may be used as a parameter in various function calls, allowing processes to be manipulated, such as adjusting the process's priority or killing it altogether.
- The current process ID is provided by a getpid() system call.  
- In the context of our assignment, the server will print its PID after it launches. 
    - The client program needs to know the server's PID to send signals to it. 
    - This is why the server's PID is one of the parameters that the client takes. We will input the server's PID when we run the client program.
    - This PID will then be used by the client to communicate with/send signals to the server.
        - This is usually done using the kill() function, which sends a signal to a process. 
        - In the context of our assignment, the signals will be SIGUSR1 and SIGUSR2.
    - The server, upon receiving the signals, will handle them accordingly. 
        - This is usually done by setting up signal handlers using the signal() or sigaction() function.

🔹 **5. How do we get the client to send the string input to the server?**
- Recall, signals can only transmit one bit at a time, and since we're only permitted to use SIGUSR1 and SIGUSR2 signals to communicate, how can we achieve this?
    - Recall, a string is made up of characters (chars), and each char has 1 byte, which consists of 8 bits.
    - If each character can be represented by 8 bits in binary, and binary is composed of 0s and 1s, then:
        - We can use for instance, SIGUSR1 for the binary digit 1, and SIGUSR2 for the binary digit 0 to encode and decode our strings.
        - This is where bitwise operations comes in to play.
        - For the client, we can iterate through each bit (binary digit) of a character, and send the server the relevant signals depending on whether it's a 0 or 1(like Morse code :smile). 
        - For example:

        - The character 'A' (ASCII value 65):
        
        - The binary representation of 'A': 01000001
        - The goal is to send each bit (0 or 1) to the server using signals. 
        - So, we need a function say, `send_bits()` to achieve this by iterating through the bits of the character and sending a signal (SIGUSR1 or SIGUSR2) to the server based on the value of each bit.

            ```
            Character 'A' (ASCII 65) - Binary: 01000001

            Bit:      0       1       0       0       0       0       0       1
            Signal:   SIGUSR2 SIGUSR1 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR2 SIGUSR1
            ```

        - In this example:
            - Each column represents a bit of the character.
            - The bit's value is shown above it (0 or 1).
            - The signal sent to the server is indicated below each bit column. 
            - A SIGUSR1 signal is sent for a bit value of 1, and a SIGUSR2 signal is sent for a bit value of 0.


🔹 **6. How do we get the server to print the string received from the client?**
- As the `send_bits` function iterates through each bit of the character, it sends the appropriate signals to the server to convey the binary representation of the character. 
- The server then interprets these signals to reconstruct the original character.
    

🔹 **7.  We need it to print the string quickly. What changes the duration of the printing?**
- Recall, the `usleep()` function is a high-precision delay mechanism that suspends a program while it waits for a signal, then the next, and so on. 
    - Depending on the system's behaviour and performance, the `usleep()` value should be adjusted accordingly. 
        - Too much of a delay can cause printing to be too slow.
        - Too less of a delay and it can cause overhead to your program reducing performance, for example, it may not print correctly.


🔹 **8. How can the server receive strings from several clients in a row without restarting?**
- This means, after a server has started, multiple clients (e.g., from different terminals or command lines), can keep sending messages, one after another, and the server would recieve them all, one at a time.
    - So, our server should have a loop where it waits for and processes incoming signals. The processing in this case would be printing the received string.
    - Recall, the `pause()`` function is used in signal handling to wait for a specific signal before proceeding with further exeution.


## 🔷 Step 5: Write the structure of directories and files
I chose to utilise my libft in this program.

```
Minitalk/
│
├── Makefile
│
├── inc/
│   ├── minitalk.h
│   └── minitalk_bonus.h 
│
├── srcs/
│   ├── client.c
│   ├── server.c
│   ├── client_bonus.c
│   └── server_bonus.c
│
└── libft/
    ├── Makefile
    │
    ├── inc/
    │
    └── src/
```

## 🔷 Step 6: Code Minitalk
Now that we understand what Minitalk entails, let's write some pseudocode to see how we might tackle this project.

- For the client:

```
//Define a function `sig_confirm` that takes a signal, which is to be received from the server
    //If the signal is SIGUSR1 or SIGUSR2
        //Print "Message recieved"
    
//Define a funtion `send_bits` that takes in the server's PID, and a character
    //Declare an integer variable `bit` to iterate through each bit of the character
    //If the binary digit at the position `bit` is `1`, send to the server SIGUSR1
        //Otherwise send to the server SIGUSR2
    //Delay the program a bit before we look at the next bit of the character

//Write a program that takes in as arguments, the PID, and "message"
    //Handle command input errors
    //Check for the correct number of arguments
        //Since the main's argv parameters is of type char, and a PID is an integer, we need to convert this value to an integer
            //Call our `send_bits` function to send the bits to the server
            //If a signal is received from the server to acknowledge reciept, call our `sig_confirm` function
```

- For the server:

```
//Define a function `sig_handler` to handle incoming signals
    //Declare a static integer variable used to iterate through the bits of a character
    //Declare a static integer variable to construct all the bits of the character 
        //Check if a character's 8 bits have been contructed
            //Print the character
            //Reset the static variables in order to process the next character
            //Send to the client, a signal to confirm a character was received

//Write a program that does not take in command line arguments other than the program name
    //Handle command input errors
    //Get the PID and print it 
    //Enter an infinate loop that continuously waits for signals to be processed
        //Call the `sig_handler` function to handle to signals
        //Wait for the next signal
```

## 🔷 Step 7: Test Minitalk

🔹 **1. Run the Server:**
- In one terminal window, run the server by executing the server executable. This will start the server process and display its PID on the terminal:

    ```
    ./server
    ```

- Take note of the displayed PID, as you'll need it to run the client.

🔹 **2. Run the Client:**
- In another terminal window, run the client by executing the client executable with the server's PID and the message you want to send. For example:

    ```
    ./client <server_pid> <message>
    ```

🔹 **3. Observe the Output:**
- The client will send the message to the server using signals. 
- We should see the message being displayed on the server terminal. 
- The message should appear character by character, and for the bonus, the "acknowledgement" should be sent for each character.
- Observe the speed of the printing at the server's end, and adjust the `usleep()` value accordingly per system's behaviour and performance.

🔹 **Repeat Testing:**
- Test our program with different messages, including special characters and longer messages, to ensure it functions as expected.
- A sample message containing around 5,000 characters (including white spaces):

    ```
    "🌍🌏🌎 Hello, 你好, Hola, Bonjour, Привет! 🌞🌝🌚

    This is a sample message with a wide range of Unicode characters from different languages and a plethora of emoticons. We've got everything from 🇺🇸 to 🇨🇳, 🇪🇸 to 🇫🇷, and 🇷🇺 too!

    Here are some examples of characters from different scripts:

    1. Latin: Lorem ipsum dolor sit amet, consectetur adipiscing elit. ☕️📚🖋️
    2. Greek: Είναι ένα παράδειγμα με ελληνικούς χαρακτήρες. 🇬🇷📖🏛️
    3. Cyrillic: Это пример с кириллическими символами. 🇷🇺📝🖥️
    4. Arabic: هذا مثال بأحرف عربية. 🇸🇦🕌🌙
    5. Hindi: यह हिन्दी में एक उदाहरण है। 🇮🇳📜🎉

    And now, let's add a few more lines in different languages:

    6. Japanese: これは異なる言語でのいくつかの文字を含むサンプルメッセージです。🇯🇵📖🗾
    7. Russian: Это дополнительные строки на русском языке. 🇷🇺📜❄️
    8. French: Voici quelques lignes supplémentaires en français. 🇫🇷📝🥖
    9. Spanish: Aquí tienes algunas líneas adicionales en español. 🇪🇸📖🌮
    10. German: Hier sind einige zusätzliche Zeilen auf Deutsch. 🇩🇪📜🍺

    And of course, we can't forget about some fun emoticons! 😄😍😎💥🎈🍕🚀

    🌟🌟🌟 Feel free to use this message for testing or any other purposes you may have! 🚀🌟✉️

    But wait, there's more! Here are some additional emoticons to brighten your day: 🌈🦄🍦🎵🎮🎉🎊🍹🎂🎁🎈📷🎸🎤🏆🎭🍔🍟🍩🍭🍬🍧🍰☕️🍷🍺🍾🥂🥃🍸🍻🥤🥄🍴🍽️🥢🍯🥜🌰🍇🍈🍉🍊🍋🍌🍍🍎🍏🍐🍑🍒🍓🥝🍅🥥🥑🍆🥔🥕🌽🌶️🥒🥦🍄🥜🌰🥐🍞🥖🥨🧀🍖🍗🥩🥓🍔🍟🍕🌭🍿🍲🥣🍛🍜🍝🍠🍢🍣🍤🍥🍡🥟🥠🍦🍧🍨🍩🍪🎂🍰🧁🥧🍫🍬🍭🍮🍯🍼🥤🍵☕️🍶🍾🍷🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🍽️🍴🍼🥤🍵☕️🍶🍾🍷🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂🥃🍸🍹🍺🍻🥄🍴🍽️🥢🥡🥠🥂"
    ```


## 🔷 Step 8: Evaluation Checklist
Ensure you pass the following as required by the project before submission:

🔸 **1. Prerequisites:**
- [ ] The project submitted has the correct directory and file names, and only includes the neccessary files: `Makefile`; `server.c`; `client.c`; (if Bonus part was done: `server_bonus.c`; `client_bonus.c`).
- [ ] The Makefile must output with the flags `-Wall`, `-Wextra` and `-Werror` and not relink.
- [ ] The Makefile must contain the rules $(NAME), all, clean, fclean and re. (And bonus rule if required.)
- [ ] There are no Norminette errors.
- [ ] There are no compilation errors. 

🔸 **2. General instructions:**
- [ ] The Makefile compiles both executables.
- [ ] The server name is "server" and it prints its PID at launch.
- [ ] The client name is "client" and it runs as follows:
    `./client <PID> <STRING>`

🔸 **3. Message transmission:**
- [ ] It's possible to pass on a message of any size.
- [ ] The server displays the messages received from the client, and prints the message correctly.

🔸 **4. Simple setup:**
- [ ] The server can recieve multiple strings without needing to be restarted. For example, the server is in a state of continous waiting to receive a message.
- [ ] If used, only one global variable is allowed, and an explanation is needed if used.
- [ ] The communication is only via the SIGUSR1 and SIGUSR2 signals.

🔸 **5. Bonus part:**
- [ ] Unicode characters are supported by both client and server, and it can be explained how it is made possible.
- [ ] The server acknowledges reciept of the message recieved, and sends the acknowledgment to the client for each signal. 


# Kill it friends! 😎
