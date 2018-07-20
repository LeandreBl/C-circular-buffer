/*
** EPITECH PROJECT, 2018
** circular_buffer API
** File description:
** C circular buffer API
*/

#ifndef _LBL_CBUFFER
# define _LBL_CBUFFER

# include <stdbool.h>
# include <stddef.h>
# include <sys/types.h>

# define FDWRITE_BUFFER (1 << 12)

struct cbuffer_s {
	int8_t *reader;
	int8_t *writer;
	int8_t *buffer;
	size_t size;
	bool empty;
};

typedef struct cbuffer_s cbuffer_t;

int cbuffer_create(cbuffer_t *buffer, size_t size);
void cbuffer_destroy(cbuffer_t *buffer);
size_t cbuffer_read(cbuffer_t *buffer, void *dest, size_t count);
size_t cbuffer_write(cbuffer_t *buffer, const void *src, size_t count);
size_t cbuffer_lsize(cbuffer_t *buffer);
ssize_t cbuffer_getbytes(cbuffer_t *buffer, void *ptr_addr, const char *delim);
void cbuffer_clear(cbuffer_t *buffer);
ssize_t cbuffer_retrieve(cbuffer_t *buffer, void *ptr_addr);
/* Store <count> bytes from <fd> into the given <buffer>, if count is < 0, it will read all available data */
ssize_t cbuffer_fdwrite(cbuffer_t *buffer, int fd, ssize_t count);

#endif /* !_LBL_CBUFFER */
