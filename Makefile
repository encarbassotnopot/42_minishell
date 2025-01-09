SOURCES = comandes.c comandes_utils.c exec_utils.c execution.c execution_utils.c fd_utils.c free_exec.c here_doc.c main.c builtins/builtin_cd.c builtins/builtins.c builtins/builtins_utils.c builtins/echo_unset.c builtins/env_exit.c builtins/pwd_export.c debug/debuger_parsing.c debug/debug_utils.c environment/environment.c environment/environment_update.c environment/environment_utils.c parsing/estructura_intermedia.c parsing/expansions.c parsing/expansions_utils.c parsing/free_parse.c parsing/lex.c parsing/lex_utils.c parsing/tokenizer.c parsing/tokenizer_utils.c signals/signals.c signals/signals_utils.c
SRC_FILES = $(addprefix $(SRC_DIR)/,$(SOURCES))
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

HDR_FLAGS = -I $(LIBFT) -I $(INCLUDE)
LIB_FLAGS = $(LIBFT_FLAGS) $(READLINE_FLAGS)
SRC_DIR = $(CURDIR)/src
BUILD_DIR = $(CURDIR)/build
BUILD_DIRS = $(sort $(dir $(OBJ_FILES)))

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g -MMD $(HDR_FLAGS)

CC = gcc

INCLUDE = $(CURDIR)/include

LIBFT = $(CURDIR)/libft
LIBFT_TARGET = $(LIBFT)/libft.so
LIBFT_FLAGS = -Wl,-rpath=$(dir $(LIBFT_TARGET)) -L $(dir $(LIBFT_TARGET)) -lft

READLINE = $(CURDIR)/readline
READLINE_TARGET = $(READLINE)/shlib/libreadline.so.8.2
READLINE_FLAGS = -Wl,-rpath=$(dir $(READLINE_TARGET)) -L $(dir $(READLINE_TARGET)) \
				 -lreadline -ltinfo

all: $(NAME)

$(LIBFT_TARGET): libft

libft:
	make -C $(LIBFT)

$(READLINE_TARGET): $(READLINE)/Makefile readline

$(READLINE)/Makefile:
	cd $(READLINE) ; ./configure

readline:
	make -C $(READLINE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(BUILD_DIRS)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIRS): 
	mkdir -p $@

$(NAME): $(READLINE_TARGET) $(LIBFT_TARGET) $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIB_FLAGS)

clean reclean:
	rm -rf $(BUILD_DIR)

deepclean: clean
	make -C $(LIBFT) fclean
	make -C $(READLINE) distclean

fclean: clean
	rm -rf $(NAME)

re: fclean all reclean

-include $(DEP_FILES)

.PHONY: all clean fclean re libft readline deepclean
