# COLORS
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY 	= \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD	= \033[1m
RED		= \033[31;1m

#---------- BASE ----------#

# FILES 
CFILES = env_lst.c check_built_ins.c sort.c finish.c ft_redirections.c ft_heredoc.c\

PARSER_FILES = ft_add_cmd.c ft_cleanup.c ft_init.c ft_main_parser.c ft_minisplit.c ft_parse_env.c ft_pipesplit.c ft_quotes.c ft_read_string.c ft_signal.c parser_utils.c 

BUILT_IN_CFILES = echo.c pwd.c exit.c env.c export.c unset.c
PIPEX_CFILES = pipex_bonus.c pipex_utils_bonus.c ft_here_doc_bonus.c last_cmd.c

# DIRECTORIES 
SRC_DIR = src/
PARSER_DIR = parser/
BUILT_IN_SRC_DIR = src/built_ins/
PIPEX_SRC_DIR = src/pipex/
OBJ_DIR = objs/

# OBJECTS
OFILES = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
PARSER_FILES = $(addprefix $(OBJ_DIR)built_ins/, $(PARSER_FILES:.c=.o))
BUILT_IN_OFILES = $(addprefix $(OBJ_DIR)built_ins/, $(BUILT_IN_CFILES:.c=.o))
PIPEX_OFILES = $(addprefix $(OBJ_DIR)pipex/, $(PIPEX_CFILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ echo "$(BLUE)Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSER_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/parser/
	@ echo "$(BLUE)Compiling File: $(GREEN)parser/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)pipex/%.o: $(PIPEX_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/pipex/
	@ echo "$(BLUE)Compiling File: $(CYAN)pipex/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)built_ins/%.o: $(BUILT_IN_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/built_ins/
	@ echo "$(BLUE)Compiling File: $(CYAN)built_ins/$(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@


#---------- FLAGS & COMPILATION ----------#

CC = clang
NAME = minishell
BONUS_NAME = 
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

all: libft $(NAME)
$(NAME): compiling $(PIPEX_OFILES) $(BUILT_IN_OFILES) $(OFILES)
	@ echo
	@ $(CC) $(CFLAGS) $(PARSER_FILES) $(PIPEX_OFILES) $(BUILT_IN_OFILES) $(OFILES) include/libft/libft.a -o $(NAME)
	@ echo "$(YELLOW)Compilation finished!$(RESET)"

libft:
	@ make --silent -C include/libft/ bonus

bonus: all $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ $(CC) $(CFLAGS) $(BONUS_OFILES) $(BONUS_ORDER_OFILES) -o $(BONUS_NAME)

#---------- CLEAN ----------#

clean:
	@ echo "$(RED)Cleaning Project ... $(RESET)"
	@ rm -f $(OFILES) $(ORDER_OFILES) $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ rm -rf $(OBJ_DIR)order_cmd/ $(OBJ_DIR) $(BONUS_OBJ_DIR)order_cmd/ $(BONUS_OBJ_DIR)
	@ make --silent -C "include/libft/" fclean
	@ echo "$(YELLOW)Project Cleaned!\n $(RESET)"

fclean: clean
	@ rm -f $(NAME) $(BONUS_NAME)

re: fclean all

compiling:
	@ echo "$(MAGENTA)Compiling Project: $(RESET)"

.PHONY: all clean fclean re bonus compiling