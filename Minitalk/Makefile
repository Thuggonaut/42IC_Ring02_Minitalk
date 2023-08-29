NAME			= client
NAMESV			= server
NAMECLB			= client_bonus
NAMESVB			= server_bonus


LIBFT			= libft


INC				= inc
HEADER			= -I inc
SRC_DIR			= src/
OBJ_DIR			= obj/
CC				= gcc
FLAGS			= -Wall -Werror -Wextra
FSANITIZE		= -fsanitize=address -g3
RM				= rm -f


SRCCL_FILES		= client
SRCSV_FILES		= server
SRCCLB_FILES	= client_bonus
SRCSVB_FILES	= server_bonus


SRCCL 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRCCL_FILES)))
OBJCL 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCCL_FILES)))

SRCSV 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRCSV_FILES)))
OBJSV 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCSV_FILES)))

SRCCLB 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRCCLB_FILES)))
OBJCLB			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCCLB_FILES)))

SRCSVB 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRCSVB_FILES)))
OBJSVB 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCSVB_FILES)))


OBJF			= .cache_exists


start:
				@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@make all


all:			$(NAME) $(NAMESV)


$(NAME):		$(OBJCL) $(OBJF)
				@$(CC) $(FLAGS) $(OBJCL) $(HEADER) libft.a -o $(NAME)


$(NAMESV):		$(OBJSV) $(OBJF)
				@$(CC) $(FLAGS) $(OBJSV) $(HEADER) libft.a -o $(NAMESV)


$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(OBJF)
				@$(CC) $(FLAGS) $(HEADER) -c $< -o $@


$(OBJF):
				@mkdir -p $(OBJ_DIR)
				@touch $(OBJF)


bonus:
				@make -C $(LIBFT)
				@cp $(LIBFT)/libft.a .
				@make allbonus


allbonus:		$(NAMECLB) $(NAMESVB)


$(NAMECLB):		$(OBJCLB) $(OBJF)
				@$(CC) $(FLAGS) $(OBJCLB) $(HEADER) libft.a -o $(NAMECLB)


$(NAMESVB):		$(OBJSVB) $(OBJF)
				@$(CC) $(FLAGS) $(OBJSVB) $(HEADER) libft.a -o $(NAMESVB)


clean:
				@$(RM) -r $(OBJ_DIR)
				@$(RM) $(OBJF) *.o, *.a, *.out
				@make clean -C $(LIBFT)
			

fclean:			clean
				@$(RM) $(NAME) $(NAMESV) $(NAMECLB) $(NAMESVB)
				@$(RM) $(LIBFT)/libft.a
				@$(RM) libft.a
				@find . -name ".DS_Store" -delete


re:				fclean all


.PHONY:			start all clean fclean re bonus
