/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** clear
*/

#include "lbuffer.h"

void lbuffer_clear(lbuffer_t *buffer)
{
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->empty = true;
}
