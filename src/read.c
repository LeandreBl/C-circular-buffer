/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** read
*/

#include "lcbuffer.h"

size_t cbuffer_read(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t i;
	int8_t *p = dest;

	if (buffer->writer == buffer->reader && buffer->empty == true)
		return (0);
	for (i = 0; i < count; ++i) {
		p[i] = *buffer->reader;
		++buffer->reader;
		if (buffer->reader >= buffer->buffer + buffer->size)
			buffer->reader = buffer->buffer;
		if (buffer->reader == buffer->writer) {
			buffer->empty = true;
			return (i + 1);
		}
	}
	return (i);
}
