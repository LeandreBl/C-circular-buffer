/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** lsize
*/

#include "lbuffer.h"

inline size_t lbuffer_lsize(lbuffer_t *buffer)
{
  if (buffer->reader < buffer->writer)
    return (buffer->buffer + buffer->size - buffer->writer + buffer->reader - buffer->buffer);
  else if (buffer->reader > buffer->writer)
    return (buffer->reader - buffer->writer);
  return ((buffer->empty) ? buffer->size : 0);
}
