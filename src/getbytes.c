/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** getbytes
*/

#include <stdlib.h>
#include <string.h>

#include "lbuffer.h"

static bool buff_cmp(lbuffer_t *buffer, const int8_t *from, const char *pattern)
{
	for (size_t i = 0; pattern[i] != '\0' && from != buffer->writer; ++i) {
		if (from == buffer->buffer + buffer->size)
			from = buffer->buffer;
		if (*from != pattern[i])
			return (false);
		++from;
	}
	return (true);
}

static ssize_t gb_err(int8_t **ptr)
{
	*ptr = NULL;
	return (0);
}

static ssize_t to_read_cmp(lbuffer_t *buffer, int8_t **ptr, const char *pattern)
{
	ssize_t rd = 0;
	size_t size = lbuffer_size(buffer);
	size_t len = strlen(pattern);
	int8_t *p;

	if (len == 0 || buffer->empty == true)
		return (gb_err(ptr));
	for (p = buffer->reader; p != buffer->writer && buff_cmp(buffer, p, pattern) == false;
	     ++p) {
		if (size-- < len)
			return (gb_err(ptr));
		if (p == buffer->buffer + buffer->size)
			p = buffer->buffer;
		++rd;
	}
	if (p == buffer->writer)
		return (gb_err(ptr));
	return (rd + len);
}

ssize_t lbuffer_getbytes(lbuffer_t *buffer, void *ptr_addr, const char *pattern)
{
	ssize_t rd = 0;
	int8_t **ptr = ptr_addr;

	rd = to_read_cmp(buffer, ptr, pattern);
	if (rd == 0)
		return (0);
	*ptr = malloc(rd + 1);
	if (*ptr == NULL)
		return (-1);
	(*ptr)[rd] = 0;
	return (lbuffer_read(buffer, *ptr, rd));
}
