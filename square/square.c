#include <stdio.h>
int main(void){
    #define SQUARE(x) ((x)*(x))
    int x = 2;
    printf("%d \n",SQUARE(++x));
}