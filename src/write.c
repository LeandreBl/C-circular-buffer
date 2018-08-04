/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** write
*/

#include "lcbuffer.h"

size_t cbuffer_write(cbuffer_t *buffer, const void *src, size_t count)
{
	size_t i;
	const int8_t *p = src;

	if (buffer->writer == buffer->reader && buffer->empty == false)
		return (0);
	if (count)
		buffer->empty = false;
	for (i = 0; i < count; ++i) {
		*buffer->writer = p[i];
		++buffer->writer;
		if (buffer->writer >= buffer->buffer + buffer->size)
			buffer->writer = buffer->buffer;
		if (buffer->writer == buffer->reader)
			return (i + 1);
	}
	return (i);
}
