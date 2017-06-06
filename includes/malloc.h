/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:55:42 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 23:24:50 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
# define MALLOC_DEBUG	0

# define BLOCK_SIZE		(sizeof(t_block))
# define BDATA(b)		((void*)((char*)b + sizeof(t_block)) + 1)

# define PAGE_SIZE		(sizeof(t_page))
# define PDATA(p)		((void*)((char*)p + sizeof(t_page)) + 1)

# define TINY_LENGTH	(4 * getpagesize())
# define TINY_ALLOC		128

# define SMALL_LENGTH	(64 * getpagesize())
# define SMALL_ALLOC	2048

# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>

typedef enum		e_mtype
{
	TINY,
	SMALL,
	LARGE
}					t_mtype;

typedef struct		s_block
{
	size_t			size;
	struct s_block	*prev;
	struct s_block	*next;
	int				is_free;
}					t_block;

typedef struct		s_page
{
	t_mtype			type;
	size_t			size;
	struct s_page	*prev;
	struct s_page	*next;
	struct s_block	*first;
}					t_page;

t_mtype				page_type(size_t size);
size_t				page_length(size_t size);
size_t				page_size(t_mtype size);
char				*page_name(t_mtype size);
t_page				*first_page(void);
void				init_block(void *ptr, size_t size);
void				init_page(void *ptr, t_mtype type, size_t size);
void				add_page(t_page *p);
t_block				*block_alloc(size_t size);
t_page				*block_parent_page(t_block *b);
void				del_page(t_page *page);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				free(void *ptr);
void				show_alloc_mem(void);
void				check_last_block_size(t_page *p, t_block *b);
void				malloc_dump(char *msg, void *ptr, size_t len);
pthread_mutex_t		*get_mmutex(void);
void				show_alloc(size_t block_size);
void				ft_putadd(void const *p);
void				ft_putstr(char *str);
void				ft_putendl(char *str);
void				ft_putchar(char c);
void				ft_putnbr(long int n);
size_t				ft_strlen(char const *str);
int					ft_isdigit(int c1);
void				*ft_strcat_chr(char *dst, const char c);
void				ft_bzero(void *b, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t len);
void				print_hex(const char *s, const size_t len);
void				print_hex_string(const char *s, const size_t len);

#endif
