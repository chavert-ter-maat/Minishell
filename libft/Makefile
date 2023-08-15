# **************************************************************************** #
#                                                                              #
#                                                         ::::::::              #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cter-maa <cter-maa@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 11:17:42 by cter-maa      #+#    #+#                  #
#    Updated: 2023/02/03 11:25:31 by cter-maa      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# VARIABLES
NAME 	= libft.a
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g
RM 		= rm -f
AR 		= ar -crs

# SOURCES
SRC =	ft_append.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strndup.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtolower.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_free_2d_array.c \

# OBJECTS
OBJ			= $(SRC:.c=.o)

# HEADERS
HEADER		= libft.h

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
	$(AR) $(NAME) $(OBJ) 
	@echo "$(GREEN)ft_libft compiled $(DEF_COLOR)"

comp: all bonus clean

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)
	@echo "$(YELLOW)ft_libft object files cleaned $(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)ft_printf object files & folders are cleaned $(DEF_COLOR)"

re: fclean $(NAME)
