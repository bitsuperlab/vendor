/*
 *  fiber.h
 *  Created on: Mar 19, 2012
 *
 *  Copyright (c) 2012 by Leo Hoo
 *  lion@9465.net
 */

#ifndef _ex_service_h__
#define _ex_service_h__

#include "fiber.h"
#include "thread.h"

namespace exlib
{

typedef void (*IDLE_PROC)();

class Service : public OSThread
{
public:
    Service();

public:
    static const int32_t type = 2;
    virtual bool is(int32_t t)
    {
        return t == type || OSThread::is(t);
    }

    virtual void Run()
    {}

public:
    void switchConext();
    static Service *current();
    static bool hasService();
    static void init();

    void RequestInterrupt(IDLE_PROC proc)
    {
        atom_xchg(&m_InterCallback, proc);
    }

    IDLE_PROC onIdle(IDLE_PROC proc)
    {
        IDLE_PROC p = m_Idle;
        m_Idle = proc;
        return p;
    }

public:
    void dumpFibers();

    Fiber* firstFiber()
    {
        linkitem* p = m_fibers.head();
        if (!p)
            return 0;

        Fiber* zfb = 0;
        return (Fiber*)((intptr_t)p - (intptr_t)(&zfb->m_link));
    }

    Fiber* nextFiber(Fiber* pThis)
    {
        linkitem* p = pThis->m_link.m_next;
        if (!p)
            return 0;

        Fiber* zfb = 0;
        return (Fiber*)((intptr_t)p - (intptr_t)(&zfb->m_link));
    }

private:
    void doInterrupt();

public:
    Fiber m_main;
    Fiber *m_running;
    Fiber *m_recycle;
    LockedList<Fiber> m_resume;

    IDLE_PROC m_Idle;
    IDLE_PROC m_InterCallback;

    List<linkitem> m_fibers;

    atomic m_switchTimes;
};

}

#endif

