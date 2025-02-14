/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tamarant <tamarant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:44:24 by tamarant          #+#    #+#             */
/*   Updated: 2020/03/15 17:30:46 by fboggs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# define BUFF_SIZE 10000
# define MAX_FD 12000
# define ULL unsigned long long
# define LD long double

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;
void				ft_putchar(char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				ft_putstr(char const *str);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_atoi(const char *str);
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
void				ft_putendl(char const *s);
char				*ft_itoa(int n);
void				ft_putnbr(int n);
char				*ft_strnew(size_t size);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *ha, const char *ne);
char				*ft_strnstr(const char *ha, const char *ne, size_t len);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				**ft_strsplit(char const *s, char c);
void				ft_free(char **res, size_t i);
int					ft_sqrt(int nb);
int					ft_iterative_factorial(int nb);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
int					ft_iterative_power(int nb, int power);
char				*ft_strjoin_free(char *s1, char *s2, int opt);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					get_next_line(const int fd, char **line);
char				**ft_strsplit_ch(char const *s, char c);
int					ft_countwords(char const *str, char c);
void				*ft_clear_table(char **tables, int i);
int					ft_atoi_base(const char *str);
size_t				ft_wordcount(const char *s, char c);
size_t				ft_wordsize(const char *s, char c);
int					number_len(int n);
int					number_len_ll(long long n);
int					number_len_ull(unsigned long long n);
char				*ft_llutoa(unsigned long long int n);
char				*ft_lltoa(long long int n);
char				*ulltoa_base(unsigned long long int value, int base);
char				*itoa_base(int value, int base);
char				*to_uppercase(char *str);
void				ft_putnbr_max(long long int nb);
char				*ft_ulltoa(unsigned long long int n);
int					ft_isinf(long double num);
int					ft_isnan(long double num);
int					ft_is_minus_inf(long double num);
ULL					ft_pow(ULL n, ULL pow);
LD					ft_pow_double(LD n, ULL pow);
int					ft_iswhitespace(char c);

int					ft_len_of_number_int(int n);

#endif
