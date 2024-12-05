NAME		=	test

CC			=	cc
CFLAGS		=	# -Wall -Wextra -Werror
RM			=	rm -rf

SRCS_DIR	=	./srcs
UTILS_DIR	=	$(SRCS_DIR)/utils
ALGO_DIR	=	$(SRCS_DIR)/algorithm
SRCS		=	$(wildcard $(SRCS_DIR)/*.c)
UTILS_SRCS	=	$(wildcard $(UTILS_DIR)/*.c)
ALGO_SRCS	=	$(wildcard $(ALGO_DIR)/*.c)


OBJS_DIR	=	./objs
OBJS		=	$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
UTILS_OBJS	=	$(UTILS_SRCS:$(UTILS_DIR)/%.c=$(OBJS_DIR)/%.o)
ALGO_OBJS	=	$(ALGO_SRCS:$(ALGO_DIR)/%.c=$(OBJS_DIR)/%.o)

INCLUDES	=	-I ./includes

RESET		=	\033[0m
BOLD		=	\033[1m
LIGHT_BLUE	=	\033[94m

MAKEFLAGS	+=	--no-print-directory

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS) $(ALGO_OBJS) $(UTILS_OBJS)
	@echo "$(BOLD)$(LIGHT_BLUE)Compile $(NAME)...$(RESET)"
	@echo "$(BOLD)$(LIGHT_BLUE)Compile now...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(UTILS_OBJS) $(ALGO_OBJS) $(INCLUDES) -o $(NAME)
	@echo "$(BOLD)$(LIGHT_BLUE)Compile $(NAME) Complete!$(RESET)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(UTILS_DIR)/%.c ./includes/*.h
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(ALGO_DIR)/%.c
	@echo "Compiling $< ..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME)...$(RESET)"
	@$(RM) $(OBJS) $(UTILS_OBJS)
	@$(RM) -r $(OBJS_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)Cleaning $(NAME) Complete!$(RESET)"

fclean:
	@echo "$(BOLD)$(LIGHT_BLUE)ALL Cleaning $(NAME)...$(RESET)"
	@$(RM) $(OBJS) $(NAME) $(UTILS_OBJS)
	@$(RM) -r $(OBJS_DIR)
	@echo "$(BOLD)$(LIGHT_BLUE)ALL Cleaning $(NAME) Complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus