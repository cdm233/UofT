#include<stdio.h>
#include<stdlib.h>

typedef struct tests
{
    int a;
} test, *testPTR;

void fun(){

}

void main(){
    test test1;
    testPTR test11;
    test11 = &test1;

    // testPTR test2 = (testPTR) malloc(sizeof(test));
    test test22;
    testPTR test2 = &test22;

    test2->a = 3;
    printf("test2.a: %d\n", test2->a);


    test1.a = 1;
    printf("test1.a: %d\n", test1.a);
    test11->a = 2;
    printf("test1.a: %d", test11->a);
}