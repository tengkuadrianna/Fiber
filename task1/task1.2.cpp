#include "../context.hpp"
#include <iostream>
#include <cstdint>
void goo()
{
    std::cout << "you called goo" << std::endl;

    exit(0);
}

void foo()
{

    puts("you called foo");

 

    Context c;
    get_context(&c);

    Context d = c;
    d.rip = (void *)goo;
    swap_context(&c, &d);
    
    exit(0);
}

int main()
{
    char data[4096];
    char *sp;

    sp = data + 4096;
    uintptr_t tmp = (uintptr_t)sp;
    tmp &= -16L;
    sp = (char *)tmp;
    sp -= 128;

    Context c;
    c.rip = (void *)foo;
    c.rsp = sp;

    set_context(&c);
}