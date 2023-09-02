# Standard
NAME				= client
SVR					= server
CLNBN				= client_bonus
SVRBN				= server_bonus

# Directories
LIBFT				= libft
INC					= inc
HEADER				= -I inc
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and Flags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
RM					= rm -f

# Source Files
SRC_CLN				= client
SRC_SVR				= server
SRC_CLNBN			= client_bonus
SRC_SVRBN			= server_bonus

# Create full paths for source and object files
SRCCL 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLN)))
OBJCL 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLN)))

SRCSV 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SVR)))
OBJSV 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SVR)))

SRCCLB 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLNBN)))
OBJCLB				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLNBN)))

SRCSVB 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SVRBN)))
OBJSVB 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SVRBN)))

# If certain objects have already been created, avoid unnecessary recompilation of source files when they haven't changed
OBJF				= .cache_exists

# Targets
start:
					@make -C $(LIBFT)
					@cp $(LIBFT)/libft.a .
					@make all
					@make bonus


all:				$(NAME) $(SVR)


$(NAME):			$(OBJCL) $(OBJF)
					@$(CC) $(FLAGS) $(OBJCL) $(HEADER) libft.a -o $(NAME)


$(SVR):				$(OBJSV) $(OBJF)
					@$(CC) $(FLAGS) $(OBJSV) $(HEADER) libft.a -o $(SVR)
					

bonus:				$(CLNBN) $(SVRBN)


$(CLNBN):			$(OBJCLB) $(OBJF)
					@$(CC) $(FLAGS) $(OBJCLB) $(HEADER) libft.a -o $(CLNBN)


$(SVRBN):			$(OBJSVB) $(OBJF)
					@$(CC) $(FLAGS) $(OBJSVB) $(HEADER) libft.a -o $(SVRBN)

# Compile object files from source files
$(OBJF):
					@mkdir -p $(OBJ_DIR)
					@touch $(OBJF)


$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(OBJF)
					@$(CC) $(FLAGS) $(HEADER) -c $< -o $@


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



//////////////////////////////////////////////////////////////////////////////////////





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
