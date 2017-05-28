/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/02 10:55:42 by gtorresa          #+#    #+#             */
/*   Updated: 2016/11/02 10:55:42 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define BLOCK_SIZE		(sizeof(t_block))
# define BDATA(b)		((void*)((char*)b + sizeof(t_block) + 1))

# define PAGE_SIZE		(sizeof(t_page))
# define PDATA(p)		((void*)((char*)p + sizeof(t_page) + 1))

# define TINY_LENGTH	(2 * getpagesize())
# define TINY_ALLOC		128

# define SMALL_LENGTH	(16 * getpagesize())
# define SMALL_ALLOC	512

# include <stdlib.h>
# include "libft.h"
# include <sys/mman.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>

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
	int				nb_block;
}					t_page;


t_mtype				page_type(size_t size);
size_t				page_length(size_t size);
size_t				page_size(t_mtype size);
t_page				*first_page(void);
void				init_block(void *ptr, size_t size);
void				init_page(void *ptr, t_mtype type, size_t size);
void				add_page(t_page *p);
t_block				*block_alloc(size_t size);
void				split_block(t_block *b, size_t mem_width);
t_page				*block_parent_page(t_block *b);
void				del_page(t_page *page);
void				*malloc(size_t size);
void				free(void *ptr);
void				get_block_len(t_block *beg, size_t size);


#endif