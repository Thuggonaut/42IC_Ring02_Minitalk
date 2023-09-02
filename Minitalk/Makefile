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

# Compiler and CFlags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra -I
RM					= rm -f

# Create full paths for source and object files
SRCCL 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(NAME)))
SRCSV 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SVR)))
SRCCLB 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(CLNBN)))
SRCSVB 				= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SVRBN)))

OBJCL 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(NAME)))
OBJSV 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SVR)))
OBJCLB				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(CLNBN)))
OBJSVB 				= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SVRBN)))

# Targets
start:
					@make -C $(LIBFT)
					@cp $(LIBFT)/libft.a .
					@make all
					@make bonus


all:				$(NAME) $(SVR)

$(NAME):			$(OBJCL) 
					@$(CC) $(CFLAGS) $(INC) $(OBJCL) libft.a -o $(NAME)

$(SVR):				$(OBJSV) 
					@$(CC) $(CFLAGS) $(INC) $(OBJSV) libft.a -o $(SVR)
					
bonus:				$(CLNBN) $(SVRBN)

$(CLNBN):			$(OBJCLB) 
					@$(CC) $(CFLAGS) $(INC) $(OBJCLB) libft.a -o $(CLNBN)

$(SVRBN):			$(OBJSVB) 
					@$(CC) $(CFLAGS) $(INC) $(OBJSVB) libft.a -o $(SVRBN)

# Compile object files from source files
$(OBJ_DIR)%.o:		$(SRC_DIR)%.c 
					@mkdir -p $(@D)
					@$(CC) $(CFLAGS) $(INC) -c $< -o $@


clean:
					@$(RM) -r $(OBJ_DIR)
					@make clean -C $(LIBFT)
			

fclean:				clean
					@$(RM) $(NAME) $(SVR) $(CLNBN) $(SVRBN)
					@$(RM) $(LIBFT)/libft.a
					@$(RM) libft.a


re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re bonus
