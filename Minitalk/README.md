Minitalk

# Standard
NAME 			= client
SVR 			= server
CLNBN 			= client_bonus
SVRBN 			= server_bonus

# Directories
LIBFT 			= libft
INC 			= inc
HEADER 			= -I inc
SRC_DIR 		= src/
OBJ_DIR 		= obj/

# Compiler and Flags
CC 				= gcc
CFLAGS 			= -Wall -Werror -Wextra
RM 				= rm -f

# Source Files
SRC 			= client server client_bonus server_bonus
OBJ 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))

# If certain objects have already been created, avoid unnecessary recompilation of source files when they haven't changed
OBJF 			= .cache_exists

# Targets
start: 			@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@make all
				@make bonus

all: 			$(NAME) $(SVR)

$(NAME) $(SVR): $(OBJ) $(OBJF)
				$(CC) $(CFLAGS) $^ $(HEADER) libft.a -o $@

bonus: 			$(CLNBN) $(SVRBN)

$(CLNBN) $(SVRBN): $(OBJ) $(OBJF)
				$(CC) $(CFLAGS) $^ $(HEADER) libft.a -o $@

$(OBJF):
				mkdir -p $(OBJ_DIR)
				touch $(OBJF)

clean:
				$(RM) -r $(OBJ_DIR)
				$(RM) $(OBJF)
				make clean -C $(LIBFT)

fclean: 		clean
				$(RM) $(NAME) $(SVR) $(CLNBN) $(SVRBN)
				$(RM) $(LIBFT)/libft.a
				$(RM) libft.a

re: 			fclean all

.PHONY: 		start all clean fclean re bonus


////////////////////////////////////////////////////////////////////////


NAME			= client
SVR				= server
CLNBN			= client_bonus
SVRBN			= server_bonus


LIBFT			= libft


INC				= inc
HEADER			= -I inc
SRC_DIR			= src/
OBJ_DIR			= obj/
CC				= gcc
FLAGS			= -Wall -Werror -Wextra
RM				= rm -f


SRC_CLN			= client
SRC_SVR			= server
SRC_CLNBN		= client_bonus
SRC_SVRBN		= server_bonus


SRCCL 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLN)))
OBJCL 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLN)))

SRCSV 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SVR)))
OBJSV 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SVR)))

SRCCLB 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_CLNBN)))
OBJCLB			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_CLNBN)))

SRCSVB 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_SVRBN)))
OBJSVB 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_SVRBN)))


OBJF			= .cache_exists


start:
				@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@make all


all:			$(NAME) $(SVR)


$(NAME):		$(OBJCL) $(OBJF)
				@$(CC) $(FLAGS) $(OBJCL) $(HEADER) libft.a -o $(NAME)


$(SVR):			$(OBJSV) $(OBJF)
				@$(CC) $(FLAGS) $(OBJSV) $(HEADER) libft.a -o $(SVR)


$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(OBJF)
				@$(CC) $(FLAGS) $(HEADER) -c $< -o $@


$(OBJF):
				@mkdir -p $(OBJ_DIR)
				@touch $(OBJF)


bonus:
				@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@make allbonus


allbonus:		$(CLNBN) $(SVRBN)


$(CLNBN):		$(OBJCLB) $(OBJF)
				@$(CC) $(FLAGS) $(OBJCLB) $(HEADER) libft.a -o $(CLNBN)


$(SVRBN):		$(OBJSVB) $(OBJF)
				@$(CC) $(FLAGS) $(OBJSVB) $(HEADER) libft.a -o $(SVRBN)


clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) $(OBJF)
				@make clean -C $(LIBFT)
			

fclean:			clean
				@$(RM) $(NAME) $(SVR	) $(CLNBN) $(SVRBN)
				@$(RM) $(LIBFT)/libft.a
				@$(RM) libft.a
				@find . -name ".DS_Store" -delete


re:				fclean all


.PHONY:			start all clean fclean re bonus


//////////////////////////////////////////////////////////////

# Standard
NAME				= client
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
LDFLAGS				= -L$(LIBFT) -lft
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


$(LIBFT)/libft.a:
					@make -C $(LIBFT)


$(NAME):			$(OBJCL) $(LIBFT) $(LIBFT)/libft.a
					$(LINK_CMD)


$(SVR):				$(OBJSV) $(LIBFT) $(LIBFT)/libft.a
					$(LINK_CMD)


bonus:				$(CLNBN) $(SVRBN)


$(CLNBN):			$(OBJCLB) $(LIBFT) $(LIBFT)/libft.a
					$(LINK_CMD)


$(SVRBN):			$(OBJSVB) $(LIBFT) $(LIBFT)/libft.a
					$(LINK_CMD)

# Compile object files from source files
$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)


$(OBJ_DIR)/%.o: 	$(SRC_DIR)/%.c $(OBJ_DIR)
					$(CC) $(CFLAGS) -c $< -o $@


clean:
					@make clean -C $(LIBFT)
					$(RM) -r $(OBJ_DIR)
			

fclean:				clean
					@$(RM) $(NAME) $(SVR) $(CLNBN) $(SVRBN)
					$(RM) $(LIBFT)/libft.a


re:					fclean all

# Phony targets represent actions not files
.PHONY:				start all clean fclean re bonus