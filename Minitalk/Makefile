# Standard
CLN					= client
SVR					= server
CLNBN				= client_bonus
SVRBN				= server_bonus

# Directories
LIBFT				= ./libft
SRC_DIR				= src/
OBJ_DIR				= obj/

# Compiler and Flags
CC					= gcc
CFLAGS				= -Wall -Werror -Wextra
LDFLAGS				= -L$(LIBFT_DIR) -lft
LINK_CMD 			= $(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
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


all:				$(CLN) $(SVR)


$(LIBFT_DIR)/libft.a:
					$(MAKE) -C $(LIBFT_DIR)


$(CLN):				$(OBJCL) $(LIBFT) $(LIBFT_DIR)/libft.a
					$(LINK_CMD)


$(SVR):				$(OBJSV) $(LIBFT) $(LIBFT_DIR)/libft.a
					$(LINK_CMD)


bonus:				$(CLNBN) $(SVRBN)


$(CLNBN):			$(OBJCLB) $(LIBFT) $(LIBFT_DIR)/libft.a
					$(LINK_CMD)


$(SVRBN):			$(OBJSVB) $(LIBFT) $(LIBFT_DIR)/libft.a
					$(LINK_CMD)

# Compile object files from source files
$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/%.o: 	$(SRC_DIR)/%.c $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@


clean:
					$(MAKE) clean -C $(LIBFT_DIR)
					$(RM) -r $(OBJ_DIR)
			

fclean:				clean
					@$(RM) $(CLN) $(SVR) $(CLNBN) $(SVRBN)
					$(RM) $(LIBFT_DIR)/libft.a


re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re bonus