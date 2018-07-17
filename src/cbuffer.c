/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** Create
*/

#include <stdlib.h>
#include <string.h>

#include "lblcbuffer.h"

int cbuffer_create(cbuffer_t *buffer, size_t size)
{
	buffer->buffer = malloc(size);
	if (buffer->buffer == NULL)
		return (-1);
	buffer->size = size;
	buffer->reader = buffer->buffer;

	buffer->writer = buffer->buffer;
	buffer->empty = true;
	return (0);
}

void cbuffer_destroy(cbuffer_t *buffer)
{
	free(buffer->buffer);
}
