/*
** EPITECH PROJECT, 2018
** lblcbuffer
** File description:
** fdwrite
*/

#include <unistd.h>

#include "lblcbuffer.h"

ssize_t cbuffer_fdwrite(cbuffer_t *buffer, int fd)
{
	int8_t block[FDWRITE_BUFFER];
	ssize_t total = 0;
	ssize_t rd;
	ssize_t wr;

	do {
		rd = cbuffer_lsize(buffer);
		if (rd > (ssize_t)sizeof(block))
			rd = (ssize_t)sizeof(block);
		rd = read(fd, block, sizeof(block));
		if (rd == -1)
			return (-1);
		wr = cbuffer_write(buffer, block, rd);
		total += wr;
	} while (rd > 0 && rd == wr);
	return (total);
}