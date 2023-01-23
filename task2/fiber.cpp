#include "fiber.hpp"

#include <iostream>
fiber::fiber(void (*func)())
{
    context_.rip = (void *)func;

    stack_bottom_ = (char *)malloc(0x400000); // 4MB stack allocation
    stack_top_ = stack_bottom_ + 0x400000;

    uintptr_t tmp = (uintptr_t)stack_top_;
    tmp &= -16L; // align to 16 bytes
    stack_top_ = (char *)tmp;
    stack_top_ -= 8 + 16 * 7; // red zone

    context_.rsp = stack_top_; // 128 bytes for red zone
}

fiber::~fiber()
{
}

Context fiber::get_context()
{
    return context_;
}

//---------------------------global scheduler IMPLEMENTATION------------------
scheduler::scheduler()
{
}

scheduler::~scheduler()
{
}

void scheduler::spawn(fiber *f)
{
    fibers_.push_back(f);
}

void scheduler::do_it()
{
    get_context(&context_);
    if (!fibers_.empty())
    {
        fiber *f = fibers_.front();
        fibers_.pop_front();
        Context c = f->get_context();
        set_context(&c);
    }
}

void scheduler::fiber_exit()
{
    set_context(&context_);
}

// global scheduler
scheduler sched;

// implementing the global fiber API
void spawn(void (*func)(), void *data)
{
    fiber *f = new fiber(func);
    sched.spawn(f);
}

void do_it()
{
    sched.do_it();
}

void fiber_exit()
{
    sched.fiber_exit();
}
