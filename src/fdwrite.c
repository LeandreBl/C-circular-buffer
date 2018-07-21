/*
** EPITECH PROJECT, 2018
** lblcbuffer
** File description:
** fdwrite
*/

#include <unistd.h>

#include "lblcbuffer.h"

static ssize_t rdsize(ssize_t rd, ssize_t count, size_t maxlen)
{
	if (rd > (ssize_t)maxlen)
		rd = (ssize_t)maxlen;
	if (count >= 0 && rd > count)
		rd = count;
	return (rd);
}

ssize_t cbuffer_fdwrite(cbuffer_t *buffer, int fd, ssize_t count)
{
	int8_t block[FDWRITE_BUFFER];
	ssize_t total = 0;
	ssize_t rd;
	ssize_t wr;

	do {
		rd = rdsize(cbuffer_lsize(buffer), count, sizeof(block));
		rd = read(fd, block, sizeof(block));
		if (rd == -1)
			return (-1);
		wr = cbuffer_write(buffer, block, rd);
		total += wr;
	} while (rd == (ssize_t)sizeof(block) && rd == wr);
	return (total);
}
