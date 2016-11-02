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

# include <stdlib.h>
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
	struct t_block	*prev;
	struct t_block	*next;
	int				is_free;
}					t_block;

typedef struct		s_page
{
	t_mtype			type;
	size_t			size;
	struct t_page	*prev;
	struct t_page	*next;
	struct t_block	*first;
	int				nb_block;
}					t_page;



void		ft_print_text(void);

#endif