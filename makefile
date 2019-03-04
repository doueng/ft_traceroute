NAME = ./ft_traceroute
LIB = ./libft/libft.a
FLAGS = -Werror -Wextra -Wall
SRC = checksum.c \
		creator.c \
		ft_freeaddr.c \
		get_ipstr.c \
		main.c \
		main_loop.c \
		parse_args.c \
		receiver.c \
		sender.c \
		x.c

SRCO = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRCO)
	@make -C libft
	gcc $(SRCO) $(LIB) -o $(NAME)

%.o: %.c
	@gcc -c $(FLAGS) $< -o $@

clean:
	@/bin/rm -f $(SRCO)
	@/bin/rm -f compile_commands.json
	@/bin/rm -rf ft_traceroute.dSYM
	@make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft

re: fclean all
