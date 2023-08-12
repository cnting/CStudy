#include <cstdio>

void test1() {
    const int number = 100;
    int number2 = 200;
    int number3 = 300;

    //常量指针(不能改值，可以改引用)
    const int *numberP = &number;
//    *numberP = 200; //报错
    numberP = &number2;

    //指针常量(可以改值，不能改引用)
    int *const numberP2 = &number2;
    *numberP2 = 300;
//    numberP2 = &number3;  //报错

    //值不能改，引用也不能改
    const int *const numberP3 = &number;
}

void test2() {
    //直接改number不行，但操作指针可以改
    const int number = 100;
    int *p = const_cast<int *>(&number);
    *p = 200;
    printf("number:%d", *p);
}

int main() {
    test2();
}
