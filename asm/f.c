    #include<stdio.h>  
    int swapint(int *a,int *b)  
    {  
        int c;  
        char *str="success!!";  
        c=*a;  
        *a=*b;  
        *b=c;  
        puts(str);                
        puts("end!");            
        printf("output??\n");   
        return 0;  
    }  
