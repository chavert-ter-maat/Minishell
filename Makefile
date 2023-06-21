# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cter-maa <cter-maa@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/04/20 11:46:11 by cter-maa      #+#    #+#                  #
#    Updated: 2023/06/21 13:47:51 by fhuisman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# VARIABLES
NAME 	= minishell
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
LDFLAGS = -lreadline
ifdef DEBUG
	CFLAGS += -g
endif

ifdef FSAN
	CFLAGS +=-fsanitize=address,undefined
endif

RM 		= rm -rf
SANITIZE = -fsanitize=address

# INCLUDES
INCLUDES	= -I ./libft -I ./libft/ft_printf

# LIBRARIES
PRINTF = ./libft/ft_printf/libftprintf.a
LIBFT = ./libft/libft.a

# SOURCES
SRC = 	SRC/main.c \
		SRC/lexer/lexer.c \
		SRC/lexer/lexer_jumptable.c \
		SRC/utils/lexer_utils.c \
		SRC/expander/expander.c \
		SRC/utils/expander_utils.c \
		SRC/utils/error.c


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
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(INCLUDES) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)minishell compiled $(DEF_COLOR)"

make comp: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(INCLUDES) $(LIBFT) $(PRINTF) -o $(NAME)
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