/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** retrieve
*/

#include <stdlib.h>

#include "lbuffer.h"

ssize_t lbuffer_retrieve(lbuffer_t *buffer, void *ptr_addr)
{
	size_t size = buffer->size - lbuffer_lsize(buffer);
	ssize_t rd;
	int8_t **pptr = ptr_addr;

	*pptr = malloc(size + 1);
	if (*pptr == NULL)
		return (-1);
	(*pptr)[size] = 0;
	rd = lbuffer_read(buffer, *pptr, size);
	return (rd);
}
