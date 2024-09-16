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
CFILES = \

BUILT_IN_CFILES = 
PIPEX_CFILES = 

# DIRECTORIES 
SRC_DIR = src/
BUILT_IN_SRC_DIR = src/built_ins/
PIPEX_SRC_DIR = src/pipex/
OBJ_DIR = objs/

# OBJECTS
OFILES = $(addprefix $(OBJ_DIR), $(CFILES:.c=.o))
BUILT-IN_OFILES = $(addprefix $(OBJ_DIR)built-ins/, $(BUILT_IN_CFILES:.c=.o))
PIPEX_OFILES = $(addprefix $(OBJ_DIR)pipex/, $(PIPEX_CFILES:.c=.o))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)
	@ echo "$(BLUE)Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)order_cmd/%.o: $(ORDER_SRC_DIR)%.c
	@ mkdir -p $(OBJ_DIR)/order_cmd/
	@ $(CC) $(CFLAGS) -c $< -o $@

#---------- BONUS ----------#

# FILES 
BONUS_CFILES = \

BONUS_ORDER_CFILES = 

# DIRECTORIES
BONUS_SRC_DIR = bonus/
BONUS_ORDER_SRC_DIR = bonus/order_cmd/
BONUS_OBJ_DIR = bonus/objs/

# OBJECTS
BONUS_OFILES = $(addprefix $(BONUS_OBJ_DIR), $(BONUS_CFILES:.c=.o))
BONUS_ORDER_OFILES = $(addprefix $(BONUS_OBJ_DIR)order_cmd/, $(BONUS_ORDER_CFILES:.c=.o))

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(CYAN)Compiling File: $(RESET)$(notdir $<)"
	@ $(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)order_cmd/%.o: $(BONUS_ORDER_SRC_DIR)%.c
	@mkdir -p $(BONUS_OBJ_DIR)/order_cmd/
	@ $(CC) $(CFLAGS) -c $< -o $@


#---------- FLAGS & COMPILATION ----------#

CC = clang
NAME = minishell
BONUS_NAME = 
CFLAGS = -Wall -Werror -Wextra -pthread -fsanitize=address -g

all: $(NAME) libft
$(NAME): compiling $(OFILES) $(ORDER_OFILES)
	@ echo
	@ $(CC) $(CFLAGS) $(OFILES) $(ORDER_OFILES) include\libft\libft.a -o $(NAME)
	@ echo "$(YELLOW)Compilation finished!$(RESET)"

libft:
	@ make -c include/libft/ bonus

bonus: all $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ $(CC) $(CFLAGS) $(BONUS_OFILES) $(BONUS_ORDER_OFILES) -o $(BONUS_NAME)

#---------- CLEAN ----------#

clean:
	@ echo "$(RED)Cleaning Project ... $(RESET)"
	@ rm -f $(OFILES) $(ORDER_OFILES) $(BONUS_OFILES) $(BONUS_ORDER_OFILES)
	@ rm -rf $(OBJ_DIR)order_cmd/ $(OBJ_DIR) $(BONUS_OBJ_DIR)order_cmd/ $(BONUS_OBJ_DIR)
	@ echo "$(YELLOW)Project Cleaned!\n $(RESET)"

fclean: clean
	@ rm -f $(NAME) $(BONUS_NAME)

re: fclean all

compiling:
	@ echo "$(MAGENTA)Compiling Project: $(RESET)"

.PHONY: all clean fclean re bonus compiling