CC		=		clang-9

CFLAGS	=		-Wall -Wextra -Werror -I .

NAME	=		libft.a

SRCS	=		ft_arraylen.c			\
				ft_arraylen_in_char.c	\
				ft_count_c_in_str.c		\
				ft_strlen.c				\
				ft_strlendelim.c		\
				ft_strdup.c				\
				ft_strcpy.c				\
				ft_strncpy.c			\
				ft_strcat.c				\
				ft_strncat.c			\
				ft_strlcat.c			\
				ft_strchr.c				\
				ft_strrchr.c			\
				ft_strstr.c				\
				ft_strnstr.c			\
				ft_strcmp.c				\
				ft_strncmp.c			\
				ft_atoi.c				\
				ft_isalpha.c			\
				ft_isdigit.c			\
				ft_isalnum.c			\
				ft_iswhitespace.c		\
				ft_isascii.c			\
				ft_isprint.c			\
				ft_iseven.c				\
				ft_toupper.c			\
				ft_tolower.c			\
				ft_memset.c				\
				ft_bzero.c				\
				ft_memcpy.c				\
				ft_memccpy.c			\
				ft_memmove.c			\
				ft_memchr.c				\
				ft_memcmp.c				\
				ft_memalloc.c			\
				ft_memdel.c				\
				ft_strnew.c				\
				ft_strdel.c				\
				ft_strclr.c				\
				ft_striter.c			\
				ft_striteri.c			\
				ft_strmap.c				\
				ft_strmapi.c			\
				ft_strequ.c				\
				ft_strnequ.c			\
				ft_strsub.c				\
				ft_strjoin.c			\
				ft_strtrim.c			\
				ft_strsplit.c			\
				ft_itoa.c				\
				ft_putchar.c			\
				ft_putchar_fd.c			\
				ft_putstr.c				\
				ft_putstr_fd.c			\
				ft_putnbr.c				\
				ft_putnbr_fd.c			\
				ft_putendl.c			\
				ft_putendl_fd.c			\
				ft_lstadd.c				\
				ft_lstnew.c				\
				ft_lstmap.c				\
				ft_lstiter.c			\
				ft_lstdelone.c			\
				ft_lstdel.c				\
				get_next_line.c			\
				ft_strndup.c			\
				ft_stristr.c			\
				ft_str_is_digits.c		\
				is_all_whitespaces.c	\
				ft_strclen.c			\
				ft_replace_substr.c

HEAD	=		libft.h

OBJS	=		$(SRCS:.c=.o)

RM		=		rm -rf

all: $(NAME)

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) -c $(SRCS)

$(NAME): $(OBJS)
	@printf '\033[38;5;29m libft building \033[38;5;50m libft.a\033[0m\n'
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@printf '\033[38;5;29m libft delete: \033[1;31m $(OBJS) \033[0m\n'
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re