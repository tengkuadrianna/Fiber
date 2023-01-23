#pragma once

//-------------------------------------------------------------------
// API for fibers
//-------------------------------------------------------------------
/// @brief terminates a fiber
///
///note call control flow within a fiber must terminate with a call
///
///to fiber_exit. Returning from a fiber without a call fiber_exit is
///
void fiber_exit();

/// @brief get pointer to data passed as part of fiber creation
/// @return pointer to data passed in at fiber creation
void * get_data();

/// @brief yield control back to scheduler
///once rescheduled fiber will restart directly following call to
//yield.
void yield();

/// @brief create a new task for execution
///if called from outsite a task it will add task to run queue, but
///nothing will happen until run() is called.
///
///if called from within a task itself, then a new task is added to
///the run queue and will execute when it is reached by the
///scheduler, no need to call run().
///
/// @param function fiber execution body
/// @param data pointer acess from running fiber
void spawn(void (*function)(), void * data = nullptr);

/// @brief run with the current set of fibers queued.
///
///returns only when all fiber have completed.
///
///Calling do_it within a fiber is undefined.
void do_it();

#include <deque>
#include <iostream>
#include "../context.hpp"
#include <unordered_set>

//fiber and scheduler classes
class fiber{
    Context context_;
    char * stack_bottom_;
    char * stack_top_;
public:
    fiber(void (*func)());
    ~fiber();
    void yielded();

    Context get_context();
    void set_context(Context *c);
};

class scheduler{
    std::deque<fiber *> fibers_;
    Context context_;
    fiber *current_fiber_;
public:
    scheduler();
    ~scheduler();
    void spawn(fiber *f);
    void do_it();
    void fiber_exit();
    void yield();
};
