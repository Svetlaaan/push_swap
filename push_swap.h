#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

# include "libft.h"
# define MAX 2147483647
# define MIN -2147483648

typedef struct s_num{
    int             num;
    int             index;
    int             block;
    struct s_num	*next;
    struct s_num	*prev;
}               t_num;

typedef struct s_what{
    t_num 			*head_a;
    t_num 			*head_b;
    t_num 			*tail_a;
    t_num 			*tail_b;

    int             stack_a;
    int             stack_b;
    int 			max_index_stack_a;
    int 			min_index_stack_a;
    int 			third_step_width; //?
}                   t_what;

int         save_argv(const char *argv, t_num **num, t_what **storage);
t_what      *new_what();
t_num		*new_num(void);
int         r_rotate(t_num **head, t_num **tail);
int         push(char c, t_what **storage);
void	    print_stacks(t_num *head_a, t_num *head_b);


#endif //PUSH_SWAP_PUSH_SWAP_H
