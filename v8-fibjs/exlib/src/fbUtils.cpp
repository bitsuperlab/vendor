/*
 * fbUtils.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: lion
 */

#ifdef WIN32

#include <windows.h>
#include <stdio.h>

#include "utils.h"

namespace exlib
{

void *_CompareAndSwap(void *volatile *Destination, void *Exchange, void *Comparand)
{
    return InterlockedCompareExchangePointer(Destination, Exchange, Comparand);
}

int32_t CompareAndSwap(volatile int32_t *Destination, int32_t old_value, int32_t new_value)
{
    return InterlockedCompareExchange((LONG *)Destination, new_value, old_value);
}

int32_t atom_add(volatile int32_t *dest, int32_t incr)
{
    return InterlockedExchangeAdd((LONG *)dest, incr) + incr;
}

int32_t atom_inc(volatile int32_t *dest)
{
    return InterlockedIncrement((LONG *)dest);
}

int32_t atom_dec(volatile int32_t *dest)
{
    return InterlockedDecrement((LONG *)dest);
}

int32_t atom_xchg(volatile int32_t *ptr, int32_t new_value)
{
    return InterlockedExchange((LONG *)ptr, new_value);
}

void *_atom_xchg(void *volatile *ptr, void *new_value)
{
    return InterlockedExchangePointer(ptr, new_value);
}

}

#endif
