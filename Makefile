NAME = minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I. -Ilibft -Ienv -Ilexer -Iparser -Iexecutor

SRCS		= main.c signals.c \
			  env/env_init.c env/env_ops.c env/env_utils.c env/env_node.c \
			  executor/exec_cmd.c executor/executor.c \
			  executor/find_path.c executor/redirections.c \
			  executor/heredoc.c executor/heredoc_child.c \
			  executor/builtins/builtins.c executor/builtins/cd.c \
			  executor/builtins/echo.c executor/builtins/env_builtin.c \
			  executor/builtins/exit.c executor/builtins/export.c \
			  executor/builtins/pwd.c executor/builtins/unset.c executor/builtins/export_print.c\
			  executor/expander/expander_str.c executor/expander/expander.c\
			  lexer/lexer_utils.c lexer/lexer_word.c lexer/lexer.c \
			  parser/parser.c parser/parser_utils.c

OBJS		= $(SRCS:.c=.o)

LIBFT_DIR	= libft
LIBFT 		= $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		rm -f $(OBJS)

fclean: clean
		$(MAKE) -C $(LIBFT_DIR) fclean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re