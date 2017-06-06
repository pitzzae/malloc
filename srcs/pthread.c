/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtorresa <gtorresa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 00:42:08 by gtorresa          #+#    #+#             */
/*   Updated: 2017/06/06 23:18:08 by gtorresa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t			*get_mmutex(void)
{
	static pthread_mutex_t	t_mutex = PTHREAD_MUTEX_INITIALIZER;

	return (&t_mutex);
}
