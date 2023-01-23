#include "../context.hpp"
#include "fiber.hpp"

void func1()
{
    char st[100];
    std::cout << "fiber 1 before" << std::endl;

    yield();
    std::cout << "fiber 1 after" << std::endl;
    fiber_exit();
}

void func2()
{
    std::cout << "fiber 2" << std::endl;
    fiber_exit();
}

int main()
{
    spawn(func1);
    spawn(func2);

    do_it();
}