#include <pthread.h>

#include "lbuffer.h"

int lbuffer_lock(lbuffer_t *buffer)
{
    return (pthread_mutex_lock(&buffer->lock));
}

int lbuffer_unlock(lbuffer_t *buffer)
{
    return (pthread_mutex_lock(&buffer->lock));
}