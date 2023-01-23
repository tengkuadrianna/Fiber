#include "../context.hpp"
#include <iostream>
#include <cstring>

void ret()
{
    std::cout << "you called ret" << std::endl;
    exit(0);
}

class fiber
{
    Context context_;
    char *stack_bottom_;
    char *stack_top_;

public:
    fiber(void (*func)())
    {
        context_.rip = (void *)func;

        stack_bottom_ = (char *)malloc(0x400000); // 4MB stack allocation
        stack_top_ = stack_bottom_ + 0x400000;

        uintptr_t tmp = (uintptr_t)stack_top_;
        tmp &= -16L; // align to 16 bytes
        stack_top_ = (char *)tmp;
        stack_top_ -= 8+16*7; // red zone

        context_.rsp = stack_top_; // 128 bytes for red zone
    }
    ~fiber()
    {
        delete[] stack_bottom_;
    }

    Context get_context()
    {
        return context_;
    }
};

void foo()
{
    std::cout << "you called foo" << std::endl;
    exit(0);
}

int main()
{
    fiber f(foo);
    Context c = f.get_context();

    set_context(&c);
}