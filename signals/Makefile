NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS = main.c main_utils.c \
       lexer/do_lex_utils.c lexer/lex_utils.c lexer/t_list_utils.c \
       lexer/lex_act.c lexer/lex_redir.c lexer/t_list_print.c \
       parsing/valid_syntax.c \
       expand/expand.c expand/expand_tokens.c expand/expand_process.c \
       expand/remove_quotes.c \
       cmd/cmd_table.c cmd/fill_cmd.c \
       heredoc/heredoc.c heredoc/heredoc_utils.c heredoc/utils_heredoc.c \
       signals/signals.c signals/signals_utils.c \
       exec/exec_pipeline.c exec/exec_child.c exec/wait.c \
       exec/path.c exec/utils.c \
       builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c \
       builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c \
       builtin/ft_unset.c builtin/utils.c \
       builtin/export_print.c builtin/ft_atoll.c builtin/get_env.c \
       garbage_collector/garbage_collector.c garbage_collector/clean_exit.c

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

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
 		--suppressions=readline.supp --track-origins=yes ./$(NAME)

.PHONY: all clean fclean re leaks
