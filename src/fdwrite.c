/*
** EPITECH PROJECT, 2018
** lbllbuffer
** File description:
** fdwrite
*/

#include <unistd.h>

#include "lbuffer.h"

static ssize_t rdsize(ssize_t rd, ssize_t count, size_t maxlen)
{
	if (rd > (ssize_t)maxlen)
		rd = (ssize_t)maxlen;
	if (count >= 0 && rd > count)
		rd = count;
	return (rd);
}

ssize_t lbuffer_fdwrite(lbuffer_t *buffer, int fd, ssize_t count)
{
	int8_t block[FDWRITE_BUFFER_SIZE];
	ssize_t total = 0;
	ssize_t rd;
	ssize_t wr;
	ssize_t to_read;

	do {
		to_read = rdsize(lbuffer_lsize(buffer), count, sizeof(block));
		rd = read(fd, block, to_read);
		if (rd == -1)
			return (-1);
		wr = lbuffer_write(buffer, block, rd);
		total += wr;
	} while (rd == to_read && rd == wr);
	return (total);
}
