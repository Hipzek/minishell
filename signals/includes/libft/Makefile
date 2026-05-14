NAME    = libft.a

CC      = cc
CFLAGS  = -Wall -Wextra -Werror
AR      = ar rcs
RM      = rm -f

# ------------ SOURCES ------------

SRCS_LIBFT = \
	libft/ft_atoi.c \
	libft/ft_bzero.c \
	libft/ft_calloc.c \
	libft/ft_isalnum.c \
	libft/ft_isalpha.c \
	libft/ft_isascii.c \
	libft/ft_isdigit.c \
	libft/ft_isprint.c \
	libft/ft_itoa.c \
	libft/ft_lstadd_back_bonus.c \
	libft/ft_lstadd_front_bonus.c \
	libft/ft_lstclear_bonus.c \
	libft/ft_lstdelone_bonus.c \
	libft/ft_lstiter_bonus.c \
	libft/ft_lstlast_bonus.c \
	libft/ft_lstmap_bonus.c \
	libft/ft_lstnew_bonus.c \
	libft/ft_lstsize_bonus.c \
	libft/ft_memchr.c \
	libft/ft_memcmp.c \
	libft/ft_memcpy.c \
	libft/ft_memmove.c \
	libft/ft_memset.c \
	libft/ft_putchar_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_split.c \
	libft/ft_strchr.c \
	libft/ft_strdup.c \
	libft/ft_striteri.c \
	libft/ft_strjoin.c \
	libft/ft_strlcat.c \
	libft/ft_strlcpy.c \
	libft/ft_strlen.c \
	libft/ft_strmapi.c \
	libft/ft_strncmp.c \
	libft/ft_strcmp.c \
	libft/ft_strnstr.c \
	libft/ft_strrchr.c \
	libft/ft_strtrim.c \
	libft/ft_substr.c \
	libft/ft_tolower.c \
	libft/ft_toupper.c

SRCS_PRINTF = \
	ft_printf/ft_print_char.c \
	ft_printf/ft_print_nbhex.c \
	ft_printf/ft_print_nbr.c \
	ft_printf/ft_print_percent.c \
	ft_printf/ft_print_ptr.c \
	ft_printf/ft_print_str.c \
	ft_printf/ft_print_type.c \
	ft_printf/ft_print_unsigned.c \
	ft_printf/ft_printf.c

SRCS_GNL = \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	get_next_line/get_next_line_bonus.c \
	get_next_line/get_next_line_utils_bonus.c

SRCS = $(SRCS_LIBFT) $(SRCS_PRINTF) $(SRCS_GNL)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
