NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc

SRCS = main.c \
       lexer/do_lex_utils.c lexer/lex_utils.c lexer/t_list_utils.c \
       parsing/valid_syntax.c \
       expand/expand.c \
       expand/remove_quotes.c \
       cmd/cmd_table.c \
       heredoc/heredoc.c \
       signals/signals.c \
       exec/exec_pipeline.c exec/path.c exec/utils.c \
       builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c \
       builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c \
       builtin/ft_unset.c builtin/utils.c \
       garbage_collector/garbage_collector.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Iincludes -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
