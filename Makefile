
# VARIABLES
NAME 	= minishell
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

ifdef DEBUG
	CFLAGS += -g
endif

ifdef FSAN
	CFLAGS +=-fsanitize=address,undefined
endif

RM 		= rm -rf
SANITIZE = -fsanitize=address
RL_PATH = $(shell brew --prefix readline)
RL_INC = -I $(RL_PATH)/include

# INCLUDES
INCLUDES	= -I./libft -I./libft/ft_printf -I./include -I$(RL_PATH)/include

# LIBRARIES

READLINE_LIB ?= -lreadline -L$(RL_PATH)/lib
PRINTF = ./libft/ft_printf/libftprintf.a
LIBFT = ./libft/libft.a

# SOURCES
SRC = 	SRC/main.c \
	 	SRC/builtins/cd_change_path.c \
		SRC/builtins/cd.c \
		SRC/builtins/echo.c \
		SRC/builtins/env.c \
		SRC/builtins/unset.c \
		SRC/builtins/export.c \
		SRC/builtins/pwd.c \
		SRC/builtins/exit.c \
		SRC/builtins/handle_builtins.c \
		SRC/environment/env_init.c \
		SRC/environment/env_utils.c \
		SRC/environment/update_env.c \
		SRC/parser/lexer_jumptable.c \
		SRC/parser/lexer.c \
		SRC/parser/expander.c \
		SRC/parser/parser.c \
		SRC/parser/parser_jumptable.c \
		SRC/utils/error.c \
		SRC/utils/expander_utils.c \
		SRC/utils/free.c \
		SRC/utils/init_shell.c \
		SRC/generic_list/generic_list.c \
		SRC/generic_list/free_functions.c \
		SRC/generic_list/compare_functions.c \
		SRC/generic_list/generic_list_utils_1.c \
		SRC/generic_list/generic_list_utils_2.c \
		SRC/executor/executor.c \
		SRC/executor/handle_errors.c \
		SRC/executor/handle_multiple_commands.c \
		SRC/executor/handle_single_command.c \
		SRC/executor/execute_non_builtin.c \
		SRC/executor/utils_executor.c \
		SRC/signals/signals.c \

# OBJECTS
OBJ			= $(SRC:.c=.o)

# COLORS
DEF_COLOR 	= \033[0;39m
GRAY 		= \033[0;90m
RED 		= \033[0;91m
GREEN 		= \033[0;92m
YELLOW 		= \033[0;93m
BLUE 		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN 		= \033[0;96m
WHITE 		= \033[0;97m
RESET		= \033[0m
	
# RULES
all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(MAKE) -C ./libft/ft_printf
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(READLINE_LIB) $(PRINTF) -o $(NAME) 
	@echo "$(GREEN)minishell compiled $(DEF_COLOR)"
	@echo "$(RED)      _______. __    __   _______  __       __         ____    ____  _______     ___       __    __  "
	@echo "$(ORANGE)     /       ||  |  |  | |   ____||  |     |  |        \   \  /   / |   ____|   /   \     |  |  |  | "
	@echo "$(YELLOW)    |   (----|   |__|  | |  |__   |  |     |  |         \   \/   /  |  |__     /  ^  \    |  |__|  | "
	@echo "$(GREEN)     \   \    |   __   | |   __|  |  |     |  |          \_    _/   |   __|   /  /_\  \   |   __   | "
	@echo "$(BLUE) .----)   |   |  |  |  | |  |____ |   ----.|   ----.       |  |     |  |____ /  _____  \  |  |  |  | "
	@echo "$(VIOLET) |_______/    |__|  |__| |_______||_______||_______|       |__|     |_______/__/     \__\ |__|  |__| "
	@echo "$(RESET)"

make go: $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_LIB) $(OBJ) $(LIBFT) $(PRINTF) -o $(NAME) 
	$(RM) $(OBJ)
	@echo "$(GREEN)minishell compiled $(DEF_COLOR)"
	@echo "$(RED)      _______. __    __   _______  __       __         ____    ____  _______     ___       __    __  "
	@echo "$(ORANGE)     /       ||  |  |  | |   ____||  |     |  |        \   \  /   / |   ____|   /   \     |  |  |  | "
	@echo "$(YELLOW)    |   (----|   |__|  | |  |__   |  |     |  |         \   \/   /  |  |__     /  ^  \    |  |__|  | "
	@echo "$(GREEN)     \   \    |   __   | |   __|  |  |     |  |          \_    _/   |   __|   /  /_\  \   |   __   | "
	@echo "$(BLUE) .----)   |   |  |  |  | |  |____ |   ----.|   ----.       |  |     |  |____ /  _____  \  |  |  |  | "
	@echo "$(CYAN) |_______/    |__|  |__| |_______||_______||_______|       |__|     |_______/__/     \__\ |__|  |__| "
	@echo "$(RESET)"
	
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<
	
debug:
	$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	$(MAKE) DEBUG=1 FSAN=1

resan: fclean fsan
	
clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./libft/ft_printf
	$(RM) $(OBJ)
	@echo "$(YELLOW)minishell object files cleaned $(DEF_COLOR)"

fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./libft/ft_printf
	$(RM) $(NAME)
	@echo "$(YELLOW)minishell executable removed $(DEF_COLOR)"

re: fclean all

echo:
	@echo $(OBJ)