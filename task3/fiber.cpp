#include "fiber.hpp"
#include <cstring>
#include <iostream>

//-----------------fiber-----------------
fiber::fiber(void (*func)())
{
    context_.rip = (void *)func;

    stack_bottom_ = (char *)malloc(0x400000); // 4MB stack allocation
    // memset(stack_bottom_, -1, 0x400000);
    stack_top_ = stack_bottom_ + 0x400000;

    uintptr_t tmp = (uintptr_t)stack_top_;
    tmp &= -16L; // align to 16 bytes
    stack_top_ = (char *)tmp;
    stack_top_ -= 8 + 16 * 7; // red zone

    context_.rsp = stack_top_; // 128 bytes for red zone
}

fiber::~fiber()
{
    free(stack_bottom_);
}

Context fiber::get_context()
{
    return context_;
}

void fiber::yielded()
{
    // the return address is at the top of the stack
    // so we can get it from there
    uintptr_t ret_addr;

    Context tmp;
    ::get_context(&tmp);

    // for(int i = 0; i < 100; i++)
    // printf("yielded tmp:%d %p\n",i, *((long long *)tmp.rsp+i));
    int i = 21;
    ret_addr = (uintptr_t) * ((long long *)tmp.rsp + i);

    // set the return address to the rip
    // printf("yielded: %p\n",ret_addr);

    context_.rip = (void *)ret_addr;

    // set the stack pointer to the next instruction
}

//-----------------scheduler-----------------
volatile int skip_yielded = 0;
scheduler::scheduler()
{
    current_fiber_ = nullptr;
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
        current_fiber_ = fibers_.front();
        fibers_.pop_front();
        Context c = current_fiber_->get_context();
        set_context(&c);
    }
}

void scheduler::fiber_exit()
{
    delete current_fiber_;
    current_fiber_ = nullptr;
    set_context(&context_);
}

void scheduler::yield()
{
    fibers_.push_back(current_fiber_);
    current_fiber_->yielded();
    Context c = current_fiber_->get_context();
    set_context(&c);
}

// global scheduler
scheduler sched;
// global data
void *data_;

// implementing the global fiber API
void spawn(void (*func)(), void *data)
{
    data_ = data;
    fiber *f = new fiber(func);
    sched.spawn(f);
}

void *get_data()
{
    return data_;
}

void do_it()
{
    sched.do_it();
}

void fiber_exit()
{
    sched.fiber_exit();
}

void yield()
{
    sched.yield();
}
