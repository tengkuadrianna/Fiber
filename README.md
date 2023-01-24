# aspassignment (fiber)



## INTRODUCTION

This project implements fiber/green thread/microthreads in C++ in three steps. We started from the very basic of context switching and gained multi-thread like behavior in the final step.

This project made by : TENGKU BINTI TENGKU (21059311)

## LINK VIDEO

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files


 ## TASK 1

 **TASK 1.1**

 In this task we used the context library to manipulate the program execution.
```C++
volatile  bool  x =0;
Context  c;
get_context(&c); //we came back to this line by setting the old context
		
std::cout << "a message" << std::endl; 
		
if(x==0){
	x=1;
	set_context(&c);
}

```


**TASK 1.2**

Manipulating PC in same function is easy. As in the same function stack frame remains same. To call a function from another function we need to switch the context of current function with the target function.

That is we need to modify the RIP and RSP of the current stack frame to the targeted stack frame. RIP have to 16byte aligned for SYS V ABI (A linux 64 bit machine). Once we ensured that , we can simply replace the RIP and RSP  of the current function context. We can then use `set_context()` to call the function. If we need to call another function from the called function we can simply use `swap_context()`


**BUILD**

Go to the sub-directory "task1"
- Run `make task1` to build the program task1.1
- Run `make task2` to build the program task1.2

# TASK 2

**TASK 2.1**

In this task we created a fiber class to maintain a single fiber. Each of the fiber needs it's own stack memory. The fiber class allocates 4MB of memory dynamically for the stack of each of the fiber. It also maintains the stack bottom, so that it can be deleted when the fiber is done executing. The stack top is again determined by  by aligning the end of that 4MB memory with 16byte. 8 bytes of the top of the stack is reserved, so that the program can write return address without accessing un-allocated memory. 16*7 bytes are reserved for red zone.

```C++
context_.rip = (void *)func;

    stack_bottom_ = (char *)malloc(0x400000); // 4MB stack allocation
    stack_top_ = stack_bottom_ + 0x400000;

    uintptr_t tmp = (uintptr_t)stack_top_;
    tmp &= -16L; // align to 16 bytes
    stack_top_ = (char *)tmp;
    stack_top_ -= 8+16*7; // red zone

    context_.rsp = stack_top_; // 128 bytes for red zone
``` 


**TASK 2.2**

Here we implemented a scheduler class that can manage several fibers. It maintains a `deque` to hold the created fibers. The entry point of start running the fibers is the `do_it()` method of the scheduler. Once a fiber calls `fiber_exit()` the scheduler starts running the  next fiber in queue.

```C++
class  scheduler{
	std::deque<fiber *> fibers_;
	Context  context_;
public:
	scheduler();
	~scheduler();
	void  spawn(fiber  *f);
	void  do_it();
	void  fiber_exit();
};
``` 



**BUILD**

Go to the sub-directory "task2"
- Run `make task1` to build the program task2.1
- Run `make task2` to build the program task2.2


# TASK 3

We implemented `yield()` in this step. When a fiber calls the `yield()` the program writes the return address of the instruction on the stack. With proper calculation we can get back that address. When yielded, we write that return address on the RIP of the fiber's context. Thus, the next time scheduler use `set_context()` with the yielded fiber's context it starts execution from right after the `yield()' call.


**BUILD**

Go to the sub-directory "task3"
- Run `make` to build the program 
