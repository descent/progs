#include <stdio.h>

#include <sys/ptrace.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>  
#include <sys/user.h>   /* For constants   
                                   ORIG_EAX etc */  
int main()  
{  
   pid_t child;  
    long err;
    child = fork();  
    if(child == 0) {  
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);  
        execl("./t", "t", NULL);  
    }  
    else {  
        wait(NULL);  
        int i, val=11;
        err = ptrace(PTRACE_PEEKDATA,
                          &i,
                          &val);  
        if (err==-1)
        {
          perror("ptrace\n");
        }

        printf("val: %d\n", val);
        #if 0
        printf("The child made a "  "system call %ld ", orig_eax);  
        ptrace(PTRACE_CONT, child, NULL, NULL);  
        #endif
    }  
    return 0;  
}  
