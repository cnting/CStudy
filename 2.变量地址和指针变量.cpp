#include <cstdio>

/**
 * 交换，但不使用额外内存
 */
void swap(int *a, int *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int main() {
    int i = 100;
    //&取地址
    int *ptr = &i;
    printf("i的地址是:%p\n", ptr);
    printf("i的值：%d\n", *ptr);

    //通过指针修改值
    *ptr = 200;
    printf("通过指针修改值：%d\n", *ptr);

    int a = 100;
    int b = 200;
    swap(&a,&b);
    printf("a:%d,b:%d",a,b);
}