/*
** EPITECH PROJECT, 2018
** circular buffer API
** File description:
** clear
*/

#include "lblcbuffer.h"

void cbuffer_clear(cbuffer_t *buffer)
{
	buffer->reader = buffer->buffer;
	buffer->writer = buffer->buffer;
	buffer->empty = true;
}
