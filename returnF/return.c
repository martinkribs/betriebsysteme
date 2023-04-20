#include <stdio.h>
int a = 0, b = 1;
void bar(int b)
{
    a = b;
    printf("bar, a=%d\n", a);
    printf("bar, b=%d\n", b);
}
void foo(int a, int b)
{
    {
        int b = a;
        int a = a + b;
    }
    printf("foo, a=%d\n", a);
    printf("foo, b=%d\n", b);
    bar(a);
}
int main(void)
{
    int b = a;
    {
        int a = 2;
        foo(a, b);
    }
    printf("main, a=%d\n", a);
    printf("main, b=%d\n", b);
    return a;
}