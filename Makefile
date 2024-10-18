SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES = $(patsubst %.c,$(BUILD_DIR)/%.d,$(SRC_FILES))

HDR_FLAGS = -I $(LIBFT)
LIB_FLAGS = -L $(LIBFT) -lft -L $(READLINE) -lreadline
BUILD_DIR = build

NAME = minishell
CFLAGS = -Wall -Wextra -g -MMD $(HDR_FLAGS)

CC = clang
LIBFT = $(CURDIR)/libft
READLINE = $(CURDIR)/readline

all: $(NAME)

$(LIBFT)/libft.a: libft

libft:
	make -C $(LIBFT)

$(READLINE)/libreadline.a: $(READLINE)/Makefile readline

$(READLINE)/Makefile:
	cd $(READLINE) ; ./configure

readline:
	make -C $(READLINE)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(BUILD_DIR):
	mkdir -p $@

$(NAME): $(READLINE)/libreadline.a $(LIBFT)/libft.a $(OBJ_FILES)
	$(CC) $(CFLAGS) $(LIB_FLAGS) -o $(NAME) $(OBJ_FILES)

clean reclean:
	rm -rf $(BUILD_DIR)

deepclean: clean
	make -C $(LIBFT) clean
	make -C $(READLINE) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT) fclean
	make -C $(READLINE) distclean

re: fclean all reclean

-include $(DEP_FILES)

.PHONY: all clean fclean re libft readline deepclean
