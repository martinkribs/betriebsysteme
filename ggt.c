#include <stdio.h>

int counter;

int gcd(int a, int b){
    counter++;
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main(int argc, char const *argv[])
{
    int eastwood = 10164; //Lokale Variable
    char guevara = 240;
    printf("result: %x\n", gcd(guevara, eastwood) ); //Konsolenausgabe
    printf("function calls needed: %d\n", counter); //via Formatstring
    return 0; 
}
