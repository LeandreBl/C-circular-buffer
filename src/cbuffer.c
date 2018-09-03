/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** Create
*/

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "lbuffer.h"

int lbuffer_create(lbuffer_t *buffer, size_t size)
{
	buffer->buffer = malloc(size);
	buffer->lock = malloc(sizeof(pthread_mutex_t));
	if (buffer->buffer == NULL || buffer->lock == NULL)
		return (-1);
	buffer->size = size;
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->empty = true;
	*buffer->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	return (0);
}

void lbuffer_destroy(lbuffer_t *buffer)
{
	free(buffer->buffer);
	free(buffer->lock);
}
