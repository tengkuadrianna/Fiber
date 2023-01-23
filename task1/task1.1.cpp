#include "../context.hpp"
#include <iostream>

int main(){

    volatile bool x =0;
    Context c;
    get_context(&c);

    std::cout << "a message" << std::endl;

    if(x==0){
        x=1;
        set_context(&c);
    }
}
