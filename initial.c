    #include <stdio.h>  
    #include <stdlib.h>  
    #include <string.h>  
      
    #define LEN 4  
    #define EXEFILE "bt"  
      
    int backtrace_m(void **buffer, int size)  
    {  
           int i = 0;  
           unsigned int _ebp = 0;  
           unsigned int _eip = 0;  
           char cmd[size][64];  
           __asm__ __volatile__(" \  
                  movl %%ebp, %0"  
                  :"=g" (_ebp)  
                  :  
                  :"memory"  
           );  
      
           for(i = 0; i < size; i++)  
           {  
                  _eip = (unsigned int)((unsigned int*)_ebp + 1);  
                  _eip = *(unsigned int*)_eip;  
                  _ebp = *(unsigned int*)_ebp;  
                  buffer[i] = (void*)_eip;  
      
                  fprintf(stderr, "%p -> ", buffer[i]);  
                  memset(cmd[i], 0, sizeof(cmd[i]));  
                  sprintf(cmd[i], "addr2line %p -e ", buffer[i]);  
                  strncat(cmd[i], EXEFILE, strlen(EXEFILE));  
                  system(cmd[i]);  
           }  
      
           return size;  
    }  
      
    static void test2(void)  
    {  
           int i = 0;  
           void *buffer[LEN] = {0};  
           backtrace_m(buffer, LEN);  
           return;  
    }  
      
    static void test1(void)  
    {  
           test2();  
    }  
      
    static void test(void)  
    {  
           test1();  
    }  
      
    int main(int argc, char *argv[])  
    {  
           test();  
           return 0;  
    }  
