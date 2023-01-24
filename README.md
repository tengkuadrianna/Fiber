# aspassignment (fiber)



## INTRODUCTION

This project implements fiber/green thread/microthreads in C++ in three steps. We started from the very basic of context switching and gained multi-thread like behavior in the final step.

This project made by : TENGKU BINTI TENGKU (21059311)

## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.uwe.ac.uk/tna2-bintiteng/aspassignment.git
git branch -M main
git push -uf origin main
```
 ## TASK 1

 **TASK1.1**

 In this task we used the context library to manipulate the program execution.
```C++
	int  main(){
		volatile  bool  x =0;
		Context  c;
		get_context(&c); //we came back to this line by setting the old context
		
		std::cout << "a message" << std::endl; 
		
		if(x==0){
			x=1;
			set_context(&c);
		}
	}
```

**TASK1.2**

Manipulating PC in same function is easy. As in the same function stack frame remains same. To call a function from another function we need to switch the context of current function with the target function.

That is we need to modify the RIP and RSP of the current stack frame to the targeted stack frame. RIP have to 16byte aligned for SYS V ABI (A linux 64 bit machine). Once we ensured that , we can simply replace the RIP and RSP  of the current function context. We can then use `set_context()` to call the function. If we need to call another function from the called function we can simply use `swap_context()`

**BUILD**

Go to the sub-directory "task1"
- Run `make task1` to build the program task1.1
- Run `make task2` to build the program task1.2


