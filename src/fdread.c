/*
** EPITECH PROJECT, 2018
** lbllbuffer
** File description:
** fdread
*/

#include <unistd.h>

#include "lbuffer.h"

static ssize_t rdsize(ssize_t wr, ssize_t count, size_t maxlen)
{
	if (wr > (ssize_t)maxlen)
		wr = (ssize_t)maxlen;
	if (count >= 0 && wr > count)
		wr = count;
	return wr;
}

ssize_t lbuffer_fdread(lbuffer_t *buffer, int fd, ssize_t count)
{
	int8_t block[FDWRITE_BUFFER_SIZE];
	ssize_t total = 0;
	ssize_t rd;
	ssize_t wr;

	do {
		rd = rdsize(lbuffer_lsize(buffer), count, sizeof(block));
		rd = lbuffer_read(buffer, block, rd);
		wr = write(fd, block, rd);
		if (wr == -1)
			return (-1);
		total += wr;
	} while (rd == (ssize_t)sizeof(block) && rd == wr);
	return (total);
}
