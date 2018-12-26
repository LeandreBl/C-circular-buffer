/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** write
*/

#include <string.h>

#include "lbuffer.h"

static size_t l_to_write(lbuffer_t *buffer, size_t to_write)
{
  size_t left;

  if (buffer->writer < buffer->reader)
    left = (size_t)(buffer->reader - buffer->writer);
  else
    left = buffer->buffer + buffer->size - buffer->writer;
  if (left > to_write)
    return (to_write);
  return (left);
}

size_t lbuffer_write(lbuffer_t *buffer, const void *src, size_t count)
{
  size_t wr;
  size_t written = 0;

  if (buffer->writer == buffer->reader && buffer->empty == false)
    return (0);
  if (count)
    buffer->empty = false;
  while (written < count) {
    wr = l_to_write(buffer, count - written);
    memcpy(buffer->writer, (const int8_t *)src + written, wr);
    buffer->writer += wr;
    written += wr;
    if (buffer->writer == buffer->buffer + buffer->size)
      buffer->writer = buffer->buffer;
    if (buffer->writer == buffer->reader)
      return (written);
  }
  return (written);
}
