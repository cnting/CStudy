#include <cstdlib>
#include <cstring>
#include "stdio.h"

void test1() {
    int i = 100;
    double d = 200;
    float f = 200;
    long l = 100;
    short s = 100;
    char c = 'D';

    printf("i的值是:%d\n", i);
    printf("d的值是:%lf\n", d);
    printf("f的值是:%f\n", f);
    printf("l的值是:%ld\n", l);
    printf("s的值是:%d\n", s);
    printf("c的值是:%c\n", c);

    //sizeof() 获取类型所占字节数
    printf("int所占字节数：%lu\n", sizeof(int));
    printf("double：%lu\n", sizeof(double));
    printf("char：%lu\n", sizeof(char));
}

/**
 * 数据类型的本质：一块连续大小的内存空间
 */
void test2() {
    //告诉c和c++编译器开辟一块连续大小的4字节的空间
    int a;
    int arr[] = {1, 2, 3, 4, 5, 6}; //内存空间大小 4*6=24
    a = 10;

    //-296939152,-296939148,-296939152,-296939128
    //&arr是数组首地址
    //&arr+1是跳过了这个数组内存的下一个内存
    //&arr 和 &arr+1 差了24 就是差了 arr 的内存空间大小
    printf("%d,%d,%d,%d", arr, arr + 1, &arr, &arr + 1);
}

struct MyStruct {
    char *name;
};
//给MyStruct取别名叫做Student
typedef struct MyStruct Student;

//给基本数据类型起别名
typedef int myInt32;

/**
 * int32_t 是 int 的别名
 */
void test3() {
    myInt32 a = 10;
    printf("%d", a);
}

/**
 * void指针 数据类型
 */
void test4() {
//    void number;  //错误，void表示任何类型
    void *ptr = malloc(100); //void*可以指向任何类型
    int * int_ptr = static_cast<int *>(ptr);  //所以转成int*也不会报错

    //什么时候用 void* ?
    //比如下面这个方法是拷贝内存，此时不关心内存里是什么类型数据时，就用void*
//    memcpy();
}

/**
 * 变量的本质：一块连续大小的内存空间的别名，通过变量可以去操作一块内存上的数据
 * 变量三要素：内存大小、名称、作用域
 */
void test5(){

}

int main() {
//    test2();
    test3();
}
