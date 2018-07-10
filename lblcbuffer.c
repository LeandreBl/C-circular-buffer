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

size_t cbuffer_read(cbuffer_t *buffer, void *dest, size_t count)
{
	size_t i;
	char *p = dest;

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

size_t cbuffer_write(cbuffer_t *buffer, const void *src, size_t count)
{
	size_t i;
	const char *p = src;

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

size_t cbuffer_lsize(cbuffer_t *buffer)
{
	if (buffer->reader < buffer->writer)
		return (buffer->buffer + buffer->size - buffer->writer +
			buffer->reader - buffer->buffer);
	else if (buffer->reader > buffer->writer)
		return (buffer->reader - buffer->writer);
	return ((buffer->empty) ? buffer->size : 0);
}

static bool is_delim(char c, const char *delim)
{
	while (*delim != 0) {
		if (*delim == c)
			return (true);
		++delim;
	}
	return (false);
}

ssize_t cbuffer_getbytes(cbuffer_t *buffer, char **pline, const char *delim)
{
	size_t rd;
	char *p = buffer->reader;

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
	*pline = calloc(rd + 1, sizeof(char));
	if (*pline == NULL)
		return (-1);
	cbuffer_read(buffer, *pline, rd);
	return (rd);
}

void cbuffer_clear(cbuffer_t *buffer)
{
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->empty = true;
}

ssize_t cbuffer_retrieve(cbuffer_t *buffer, char **pptr)
{
	size_t size = buffer->size - cbuffer_lsize(buffer);
	ssize_t rd;

	*pptr = malloc(size + 1);
	if (*pptr == NULL)
		return (-1);
	(*pptr)[size] = 0;
	rd = cbuffer_read(buffer, *pptr, size);
	return (rd);
}
