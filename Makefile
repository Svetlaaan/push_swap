CHECKER = checker

PUSH_SWAP = push_swap

CC = gcc -g -Wall -Wextra -Werror

SRC_DIR = src/

PRINTF_DIR = printf/

PRINTF_A = printf/libftprintf.a

OBJ_DIR = obj/

PS_SRC = push_swap.c new_and_free.c operations.c set_index.c \
sort_small.c sorting_al.c check_smthng.c

CHECKER_SRC = checker.c check_smthng.c new_and_free.c operations.c set_index.c \
check_smthng.c

CHECKER_OBJ = ${CHECKER_SRC:c=o}

PS_OBJ = ${PS_SRC:c=o}

all: $(CHECKER) $(PUSH_SWAP)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) -I printf/ -I include/ -c -o $@ $^

$(CHECKER): $(addprefix $(OBJ_DIR), $(CHECKER_OBJ))
	make -C printf/
	$(CC) $(addprefix $(OBJ_DIR), $(CHECKER_OBJ)) $(PRINTF_DIR)libftprintf.a -I printf/ -I includes/ -o $(CHECKER)
	echo "\033[34m$(CHECKER)   was compiled\033[m"

$(PUSH_SWAP): $(PRINTF_A) $(addprefix $(OBJ_DIR), $(PS_OBJ)) printf/libftprintf.a
	$(CC) $(addprefix $(OBJ_DIR), $(PS_OBJ)) $(PRINTF_DIR)libftprintf.a -I printf/ -o $(PUSH_SWAP)
	echo "\033[34m$(PUSH_SWAP) was compiled\033[m"

$(PRINTF_A):
    $(MAKE) -C $(PRINTF_DIR)

clean:
	make -C $(PRINTF_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(PRINTF_DIR) fclean
	rm -f $(CHECKER)
	echo "\033[31m$(CHECKER)   was deleted"
	rm -f $(PUSH_SWAP)
	echo "$(PUSH_SWAP) was deleted\033[m"

re: fclean all