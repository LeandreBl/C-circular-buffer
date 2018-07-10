/*
** EPITECH PROJECT, 2018
** circular_buffer API
** File description:
** C circular buffer API
*/

#ifndef LBL_CIRCULAR_BUFFER_API_
# define LBL_CIRCULAR_BUFFER_API_

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

struct cbuffer_s {
	char *reader;
	char *writer;
	char *buffer;
	size_t size;
	bool empty;
};

typedef struct cbuffer_s cbuffer_t;

int cbuffer_create(cbuffer_t *buffer, size_t size);
void cbuffer_destroy(cbuffer_t *buffer);
size_t cbuffer_read(cbuffer_t *buffer, void *dest, size_t count);
size_t cbuffer_write(cbuffer_t *buffer, const void *src, size_t count);
size_t cbuffer_lsize(cbuffer_t *buffer);
ssize_t cbuffer_getbytes(cbuffer_t *buffer, char **pptr, const char *delim);
void cbuffer_clear(cbuffer_t *buffer);
ssize_t cbuffer_retrieve(cbuffer_t *buffer, char **pptr);

#endif /* !LBL_CIRCULAR_BUFFER_API_ */
