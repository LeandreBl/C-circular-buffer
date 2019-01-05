/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** size
*/

#include "lbuffer.h"

inline size_t lbuffer_size(lbuffer_t *buffer)
{
  return (buffer->size - lbuffer_lsize(buffer));
}
