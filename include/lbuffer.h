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
# include <sys/cdefs.h>

# define FDWRITE_BUFFER_SIZE (1 << 12)

struct lbuffer_s {
	int8_t *reader;
	int8_t *writer;
	int8_t *buffer;
	size_t size;
	bool empty;
};

typedef struct lbuffer_s lbuffer_t;

int lbuffer_create(lbuffer_t *buffer, size_t size) __THROW __nonnull((1));
void lbuffer_destroy(lbuffer_t *buffer) __nonnull((1));

size_t lbuffer_read(lbuffer_t *buffer, void *dest, size_t count) __THROW __nonnull((1, 2));
size_t lbuffer_write(lbuffer_t *buffer, const void *src, size_t count) __THROW __nonnull((1, 2));

size_t lbuffer_lsize(lbuffer_t *buffer) __THROW __nonnull((1));
size_t lbuffer_size(lbuffer_t *buffer) __THROW __nonnull((1));

ssize_t lbuffer_getbytes(lbuffer_t *buffer, void *ptr_addr, const char *delim) __THROW __nonnull((1, 2, 3));

void lbuffer_clear(lbuffer_t *buffer) __THROW __nonnull((1));

ssize_t lbuffer_retrieve(lbuffer_t *buffer, void *ptr_addr) __THROW __nonnull((1, 2));

ssize_t lbuffer_fdwrite(lbuffer_t *buffer, int fd, ssize_t count) __THROW __nonnull((1));
ssize_t lbuffer_fdread(lbuffer_t *buffer, int fd, ssize_t count) __THROW __nonnull((1));

int lbuffer_resize(lbuffer_t *buffer, size_t newsize) __THROW __nonnull((1));

#endif /* !_LBL_CBUFFER */
