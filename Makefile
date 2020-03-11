CHECKER = checker
PUSH_SWAP = push_swap

HEADER_NAME = push_swap.h
PRINTF_A = printf/libftprintf.a

INC_DIR = ./inc/
INC_PRINTF = ./printf/inc/
SRC_DIR = ./src/
OBJ_DIR = ./obj/

PS_SRC_NAME = push_swap.c new_and_free.c operations.c set_index.c \
sort_small.c sorting_al.c check_smthng.c

CHECKER_SRC_NAME = checker.c check_smthng.c new_and_free.c operations.c set_index.c \
sorting_al.c sort_small.c

HEADER = $(addprefix $(INC_DIR), $(HEADER_NAME))

SRC_PS = $(addprefix $(SRC_DIR), $(PS_SRC_NAME))
SRC_CHECK = $(addprefix $(SRC_DIR), $(PS_SRC_NAME))
OBJ_CHECKER = $(addprefix $(OBJ_DIR), $(CHECKER_SRC_NAME:.c=.o))
OBJ_PS = $(addprefix $(OBJ_DIR), $(PS_SRC_NAME:.c=.o))

CC = gcc
FLAGS = -Wall -Wextra -Werror
GCC_PRINTF = -L ./printf -l ftprintf

all: $(CHECKER) $(PUSH_SWAP)

$(PUSH_SWAP): $(OBJ_DIR) $(OBJ_PS) $(PRINTF_A) $(HEADER)
	$(CC) $(GCC_PRINTF) $(addprefix -I, $(INC_DIR)) $(OBJ_PS) $(FLAGS) -o $(PUSH_SWAP)

$(CHECKER): $(OBJ_DIR) $(OBJ_CHECKER) $(PRINTF_A) $(HEADER)
	$(CC) $(GCC_PRINTF) $(addprefix -I, $(INC_DIR)) $(OBJ_CHECKER) $(FLAGS) -o $(CHECKER)

$(OBJ_DIR):
	@mkdir -p obj

$(PRINTF_A):
	@make -C printf/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) -c -I $(INC_DIR) -I $(INC_PRINTF) $(FLAGS) $< -o $@

clean:
	make -C ./printf clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C ./printf fclean
	rm -f $(CHECKER)
	echo "\033[31m$(CHECKER)   was deleted"
	rm -f $(PUSH_SWAP)
	echo "$(PUSH_SWAP) was deleted\033[m"

re: fclean all