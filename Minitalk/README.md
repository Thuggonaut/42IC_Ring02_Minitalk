#include "../inc/minitalk_bonus.h"

static void	sig_confirm(int sig) //Define a static function that takes in an integer representing a signal, and acknowledges reciept upon receiving it
{
	if (sig == SIGUSR1)
		ft_printf("signal received");
	else
		ft_printf("signal received");
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
	int		*msg; //Declaring an integer pointer instead of a character pointer, allows the handling of not only ASCII characters but also Unicode characters. See #1

	if (argc == 3) 
	{
		pid = ft_atoi(argv[1]); 
		msg = (int*)argv[2];
		while (*msg != '\0') 
		{
			signal(SIGUSR1, sig_confirm); //Each time a signal is received, acknowledge reciept
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
#1	Character Encoding:
		- Unicode characters can be encoded using various formats such as UTF-8, UTF-16, and UTF-32. 
			- Each of these encodings uses a different number of bytes to represent characters. 
			- UTF-8, for example, uses 1 to 4 bytes to encode characters. 
		- Using an `int *` allows you to handle these various encodings without worrying about truncating characters or losing 
		  information.
		- Using a `char *`, risks runing into limitations when dealing with characters that require more than one byte.
*/




//////////////////////////////////////////////////////////////////////////////////////



# Standard
NAME				= client
SVR					= server
CLNBN				= client_bonus
SVRBN				= server_bonus

# Directories
LIBFT				= libft
INC					= inc
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and Flags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

# Source Files
SRC 				= $(addprefix $(SRC_DIR), client.c server.c client_bonus.c server_bonus.c)

# Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

# If certain objects have already been created, avoid unnecessary recompilation of source files when they haven't changed
OBJF				= .cache_exists

# Targets
start:
					@make -C $(LIBFT)
					@cp $(LIBFT)/libft.a .
					@make all
					@make bonus


all:				$(NAME) $(SVR)


$(NAME):			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) libft.a -o $(NAME)


$(SVR):				$(OBJ)
					@$(CC) $(CFLAGS) $(INC) libft.a -o $(SVR)
					

bonus:				$(CLNBN) $(SVRBN)


$(CLNBN):			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) libft.a -o $(CLNBN)


$(SVRBN):			$(OBJ)
					@$(CC) $(CFLAGS) $(INC) libft.a -o $(SVRBN)

# Compile object files from source files
$(OBJF):
					@mkdir -p $(OBJ_DIR)
					@touch $(OBJF)


$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(OBJF)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@


clean:
					@$(RM) -r $(OBJ_DIR)
					@$(RM) $(OBJF)
					@make clean -C $(LIBFT)
			

fclean:				clean
					@$(RM) $(NAME) $(SVR) $(CLNBN) $(SVRBN)
					@$(RM) $(LIBFT)/libft.a
					@$(RM) libft.a


re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re bonus
