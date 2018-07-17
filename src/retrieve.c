/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** retrieve
*/

#include <stdlib.h>

#include "lblcbuffer.h"

ssize_t cbuffer_retrieve(cbuffer_t *buffer, int8_t **pptr)
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
