SRC		=	src/main.c \
			src/parsing.c \
			src/parsing_cmd.c \
			src/utils.c \

NAME	= pipex
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar rcs

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ		= $(SRC:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			$(RM) $(OBJ)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re
