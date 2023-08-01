
# VARIABLES
NAME 	= minishell
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -I./libft -I./libft/ft_printf -I./include -I$(RL_PATH)/include
ifdef DEBUG
	CFLAGS += -g
endif

ifdef FSAN
	CFLAGS +=-fsanitize=address,undefined
endif

RM 		= rm -rf
SANITIZE = -fsanitize=address
# RL_PATH = ./Users/cter-maa/.brew/opt/readline
RL_PATH = $(shell brew --prefix readline)
RL_INC = -I $(RL_PATH)/include

# INCLUDES
INCLUDES	= -I./libft -I./libft/ft_printf -I./include -I$(RL_PATH)/include

# LIBRARIES
LIBS = -lreadline -L$(RL_PATH)/lib -L$(PRINTF) -L$(LIBFT)
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
		SRC/parser/lexer_jumptable.c \
		SRC/parser/lexer.c \
		SRC/parser/expander.c \
		SRC/parser/parser.c \
		SRC/parser/parser_jumptable.c \
		SRC/utils/error.c \
		SRC/utils/expander_utils.c \
		SRC/utils/handle_errors.c \
		SRC/utils/free.c \
		SRC/generic_list/generic_list.c \
		SRC/generic_list/free_functions.c \
		SRC/generic_list/compare_functions.c \
		SRC/executor/executor.c \
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
	
# RULES
all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(MAKE) -C ./libft/ft_printf
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $(INCLUDES) $(LIBFT) $(PRINTF) -o $(NAME)  
	@echo "$(GREEN)minishell compiled $(DEF_COLOR)"

make go: $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) $(INCLUDES) $(LIBFT) $(PRINTF) -o $(NAME) 
	$(RM) $(OBJ)
	@echo "$(GREEN)SHELL YEAH! $(DEF_COLOR)"

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