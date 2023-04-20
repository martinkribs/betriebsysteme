#include <stdio.h>
int global_uninitialized;
int global_initialized = 4711;

void uboot(void){}

int main(void){
    int local;
    printf("%p\n%p\n%p\n%p\n",
        &global_uninitialized,
        &global_initialized,
        &uboot,
        &local);
    return 0;
}