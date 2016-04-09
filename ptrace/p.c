#include <sys/ptrace.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <unistd.h>  
#include <sys/user.h>   /* For constants   
                                   ORIG_EAX etc */  
int main()  
{  
   pid_t child;  
    long orig_eax;  
    child = fork();  
    if(child == 0) {  
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);  
        execl("./t", "t", NULL);  
    }  
    else {  
        wait(NULL);  
        #if 0
        orig_eax = ptrace(PTRACE_PEEKUSER,   
                          child, 4 * ORIG_EAX,   
                          NULL);  
        printf("The child made a "  
               "system call %ld ", orig_eax);  
        ptrace(PTRACE_CONT, child, NULL, NULL);  
        #endif
    }  
    return 0;  
}  
