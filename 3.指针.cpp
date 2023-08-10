#include <cstdio>

/**
 * 二级指针
 */
void test1() {
    int num = 12;
    //p是指针，记录num的地址
    int *p = &num;
    //s_p记录p指针的地址
    int **s_p = &p;
    printf("p的值：%p,s_p的值:%p\n", p, s_p);

    printf("p解引用:%d\n", *p);
    printf("s_p两次解引用:%d\n", **s_p);
}

/**
 * 数组与数组指针
 */
void test2() {
    int arr[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; i++) {
        printf("%d\n", arr[i]);
    }
    //arr的值 = arr地址的值 = arr[0]地址的值（首地址）
    printf("arr = %p\n", arr);
    printf("&arr = %p\n", &arr);
    printf("&arr[0] = %p\n", &arr[0]);

    //获取数组指针，数组指针指向的是数组的首地址
    int *arr_p = arr;
    printf("%d\n", *arr_p);
    //指针移到下一个
    arr_p++;
    printf("%d\n", *arr_p);

    //使用指针遍历数组并修改值
    arr_p = arr;
    for (int i = 0; i < 4; i++) {
        //移动arr_p的方式
//        *arr_p = *arr_p * 10;
//        arr_p++;

        //不移动arr_p的方式
        *(arr_p + i) = *(arr_p + i) * 10;
    }

    //使用指针遍历修改值
    arr_p = arr;
    for (int i = 0; i < 4; i++) {
        printf("位置%d的值：%d\n", i, *(arr_p + i));
    }
}

void add(int num1, int num2) {
    printf("num1 + num2 = %d\n", num1 + num2);
}

void mins(int num1, int num2) {
    printf("num1 - num2 = %d\n", num1 - num2);
}

void operate(void(method)(int, int), int num1, int num2) {
    method(num1, num2);
}

//函数指针
void test3() {
    //函数指针的定义：
    //方法返回值类型(*方法的名称)(方法的参数)
    void (*add_p)(int, int);
    add_p = add;

    operate(add, 1, 2);
    operate(mins, 1, 2);

}

int main() {
//    test1();
//    test2();
    test3();
}
