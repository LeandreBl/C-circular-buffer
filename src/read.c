/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** read
*/

#include <string.h>
#include <stdio.h>

#include "lbuffer.h"

static size_t l_to_read(lbuffer_t *buffer, size_t to_read)
{
  size_t left;

  if (buffer->reader < buffer->writer) {
    left = (size_t)(buffer->writer - buffer->reader);
    if (left > to_read)
      return (to_read);
    return (left);
  }
  left = buffer->buffer + buffer->size - buffer->reader;
  if (left > to_read)
    return (to_read);
  return (left);
}

size_t lbuffer_read(lbuffer_t *buffer, void *dest, size_t count)
{
  size_t rd;
  size_t read = 0;

  if (buffer->writer == buffer->reader && buffer->empty == true)
    return (0);
  while (read < count) {
    rd = l_to_read(buffer, count - read);
    memcpy((int8_t *)dest + read, buffer->reader, rd);
    buffer->reader += rd;
    read += rd;
    if (buffer->reader == buffer->buffer + buffer->size)
      buffer->reader = buffer->buffer;
    if (buffer->reader == buffer->writer) {
      buffer->empty = true;
      return (read);
    }
  }
  return (read);
}
