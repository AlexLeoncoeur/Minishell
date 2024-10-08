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
CFILES = hola.c\

BUILT_IN_CFILES = echo.c pwd.c
PIPEX_CFILES = pipex_bonus.c pipex_utils_bonus.c ft_here_doc_bonus.c last_cmd.c

# DIRECTORIES 
SRC_DIR = src/
BUILT_IN_SRC_DIR = src/built_ins/
PIPEX_SRC_DIR = src/pipex/
OBJ_DIR = objs/

# OBJECTS
OFILES = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
BUILT_IN_OFILES = $(addprefix $(OBJ_DIR)built_ins/, $(BUILT_IN_CFILES:.c=.o))
PIPEX_OFILES = $(addprefix $(OBJ_DIR)pipex/, $(PIPEX_CFILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ echo "$(BLUE)Compiling File: $(RESET)$(notdir $<)"
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
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

all: libft $(NAME)
$(NAME): compiling $(OFILES) $(PIPEX_OFILES) $(BUILT_IN_OFILES)
	@ echo
	@ $(CC) $(CFLAGS) $(PIPEX_OFILES) $(BUILT_IN_OFILES) include/libft/libft.a -o $(NAME)
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