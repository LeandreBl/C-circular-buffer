/*
** EPITECH PROJECT, 2018
** lbuffer
** File description:
** resize
*/

#include <string.h>

#include "lbuffer.h"

int lbuffer_resize(lbuffer_t *buffer, size_t newsize)
{
	lbuffer_t temp;
	char buff[4096];
	size_t rd;
	size_t wr;

	if (lbuffer_create(&temp, newsize) == -1)
		return (-1);
	do {
		rd = lbuffer_read(buffer, buff, sizeof(buff));
		wr = lbuffer_write(&temp, buff, rd);
	} while (rd > 0 && rd == wr);
	lbuffer_destroy(buffer);
	memcpy(buffer, &temp, sizeof(temp));
	return (0);
}
