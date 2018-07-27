/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** getbytes
*/

#include <stdlib.h>

#include "lblcbuffer.h"

static bool is_delim(int8_t c, const char *delim)
{
	while (*delim != 0) {
		if (*delim == c)
			return (true);
		++delim;
	}
	return (false);
}

ssize_t cbuffer_getbytes(cbuffer_t *buffer, void *ptr_addr, const char *delim)
{
	size_t rd;
	int8_t *p = buffer->reader;
	int8_t **pline = ptr_addr;

	if (p == buffer->writer) {
		*pline = NULL;
		return (0);
	}
	for (rd = 1; p != buffer->writer && is_delim(*p, delim) == false; ++rd) {
		if (p >= buffer->buffer + buffer->size)
			p = buffer->buffer;
		else
			++p;
	}
	if (p == buffer->writer) {
		*line = NULL;
		return (0);
	}
	*pline = malloc((rd + 1) * sizeof(*buffer->buffer));
	if (*pline == NULL)
		return (-1);
	cbuffer_read(buffer, *pline, rd);
	(*pline)[rd] = 0;
	return (rd);
}
