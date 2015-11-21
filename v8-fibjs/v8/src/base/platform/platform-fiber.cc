#include "src/v8.h"
#include "src/profiler/sampler.h"
#include <exlib/include/fiber.h>
#include <exlib/include/service.h>
#include <fc/thread/thread.hpp>


#ifdef _WIN32

#ifdef CreateMutex
#undef CreateMutex
#endif

#ifdef CreateSemaphore
#undef CreateSemaphore
#endif

#endif

#if 1

inline int64_t getTime();

namespace v8
{

namespace internal
{

void Sampler::DoSample()
{
}

}

namespace base
{

class Thread::PlatformData : public exlib::OSThread
{
public:
    PlatformData(Thread* pThis) : thread(pThis)
    {}

public:
    virtual void Run()
    {
        thread->NotifyStartedAndRun();
    }

private:
    Thread *thread;
};

Thread::Thread(const Options &options) :
    data_(new PlatformData(this)), stack_size_(options.stack_size()), start_semaphore_(NULL)
{
    data_->Ref();
    set_name(options.name());
}

Thread::~Thread()
{
    data_->Unref();
}

void Thread::set_name(const char *name)
{
    strncpy(name_, name, sizeof(name_));
    name_[sizeof(name_) - 1] = '\0';
}

void Thread::Start()
{
    data_->start();
}

void Thread::Join()
{
    data_->join();
}

Thread::LocalStorageKey Thread::CreateThreadLocalKey()
{
    return fc::thread::tlsAlloc();
}

void Thread::DeleteThreadLocalKey(LocalStorageKey key)
{
    fc::thread::tlsFree(static_cast<int>(key));
}

void *Thread::GetThreadLocal(LocalStorageKey key)
{
    return fc::thread::tlsGet(static_cast<int>(key));
}

void Thread::SetThreadLocal(LocalStorageKey key, void *value)
{
    fc::thread::tlsPut(static_cast<int>(key), value);
}

void OS::Sleep(TimeDelta interval)
{
    fc::sleep_until(fc::time_point::now() + fc::milliseconds(500));
}

}

}

#endif
