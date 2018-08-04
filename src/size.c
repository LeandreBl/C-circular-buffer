/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** size
*/

#include "lcbuffer.h"

size_t cbuffer_size(cbuffer_t *buffer)
{
	return (buffer->size - cbuffer_lsize(buffer));
}
