/**
 * \file lbuffer.h
 * \brief circular buffer implmentation
 * \author Blanchard Leandre
 * \version 0.4
 * \date 10 january 2019
 *
 * Circular buffer API in C
 *
 */

#ifndef _LBL_CBUFFER
#define _LBL_CBUFFER

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/cdefs.h>

#define FDWRITE_BUFFER_SIZE (1 << 12)

struct lbuffer_s {
	int8_t *reader;
	int8_t *writer;
	int8_t *buffer;
	size_t size;
	bool empty;
};

typedef struct lbuffer_s lbuffer_t;

/**
 * \brief This is the constructor, this should be call before anything
 *
 * \param size The total size in bytes, of the buffer
 * \return 0 on success, -1 on error
 */
int lbuffer_create(lbuffer_t *buffer, size_t size) __THROW __nonnull((1));

/**
 * \brief This is the destructor, it performs a cleanup on allocated ressources
 */
void lbuffer_destroy(lbuffer_t *buffer) __nonnull((1));

/**
 * \brief Reads from the circular buffer and writes into the destination buffer
 *
 * \param dest The destination buffer that will store the bytes
 * \param count The amount of bytes to be copied
 * \return The amount of read bytes (can be less than requested if there is not enough data in the
 * circular buffer)
 */
size_t lbuffer_read(lbuffer_t *buffer, void *dest, size_t count) __THROW __nonnull((1, 2));

/**
 * \brief Writes from the given source buffer into the circular buffer
 *
 * \param src The source buffer from which bytes are copied
 * \param count The amount of bytes to be written
 * \return The amount of written bytes (can be less than requested if there is not enough space left
 * in the circular buffer)
 */
size_t lbuffer_write(lbuffer_t *buffer, const void *src, size_t count) __THROW __nonnull((1, 2));

/**
 * \brief Calculate the unused space in the buffer
 *
 * \return The current amount of bytes that can be stored in the buffer
 */
size_t lbuffer_lsize(lbuffer_t *buffer) __THROW __nonnull((1));

/**
 * \brief Calculate the used space in the buffer
 *
 * \return The current amount of bytes stored in the buffer
 */
size_t lbuffer_size(lbuffer_t *buffer) __THROW __nonnull((1));

/**
 * \brief Get all the bytes from the buffer until a pattern is found
 *
 * This function search the given "delim" pattern and allocates enough memory to store the result in
 * *ptr_addr if not found, the function returns 0 and *ptr_addr is set to NULL The allocated buffer
 * will then need to be freed using FREE(3)
 *
 * \param ptr_addr The address of the pointer that will store the data
 * \param delim The delimitation pattern
 * \return The number of bytes copied or -1 on error
 */
ssize_t lbuffer_getbytes(lbuffer_t *buffer, void *ptr_addr, const char *delim) __THROW
	__nonnull((1, 2, 3));

/**
 * \brief Clears the buffer content
 *
 * This function does not free the allocated memory
 */
void lbuffer_clear(lbuffer_t *buffer) __THROW __nonnull((1));

/**
 * \brief Retrieve the entire circular buffer, in ascending order
 *
 * This function allocated memory and store the result in *ptr_addr
 * The allocated buffer will then need to be freed using FREE(3)
 *
 * \param ptr_addr the address of the pointer that will store the buffer
 * \return The amount of bytes copied, -1 on error
 */
ssize_t lbuffer_retrieve(lbuffer_t *buffer, void *ptr_addr) __THROW __nonnull((1, 2));

/**
 * \brief Writes from the given file descriptor into the circular buffer
 *
 * Note that if 'count' is negative, the function will read until:
 * - there is not enough space in the circular buffer
 * - there is no more data available at the moment in the file descriptor
 *
 * \param fd The file descriptor from which bytes will be read
 * \param count The amount of bytes to be read
 * \return The amount of written bytes (can be less than requested) or -1 on error
 */
ssize_t lbuffer_fdwrite(lbuffer_t *buffer, int fd, ssize_t count) __THROW __nonnull((1));

/**
 * \brief Reads from the circular buffer into the given file descriptor
 *
 * Note that if 'count' is negative, the function will write until:
 * - there is no more data available in the circular buffer
 * - the function couldn't write more in the file descriptor
 *
 * \param fd The file descriptor from which bytes will be written
 * \param count The amount of bytes to be written
 * \return The amount of read bytes (can be less than requested) or -1 on error
 */
ssize_t lbuffer_fdread(lbuffer_t *buffer, int fd, ssize_t count) __THROW __nonnull((1));

/**
 * \brief Resize the internal buffer maximum size
 *
 * This function is not thread safe
 *
 * \param newsize The new total size of the buffer
 * \return 0 on success, -1 on error
 */
int lbuffer_resize(lbuffer_t *buffer, size_t newsize) __THROW __nonnull((1));

#endif /* !_LBL_CBUFFER */
