#include <cstdio>
#include <cstdlib>
#include <cstring>

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

/**
 * 函数指针
 */
void test3() {
    //函数指针的定义：
    //方法返回值类型(*方法的名称)(方法的参数)
    void (*add_p)(int, int);
    add_p = add;

    operate(add, 1, 2);
    operate(mins, 1, 2);

}

/**
 * 指针也是一种数据类型，占用4个字节，不管是int* 还是 double* 都是4字节，因为它存的是一个内存地址
 *
 */
void test4() {
    int a = 100;
    int *ff = &a; //虽说是a的地址，但也可以把ff看做是一个数组。因为数组指针存的就是数组的首地址
    //会往后移动4个字节
    ff += 1;

    //所以 char** 可以看做是二维数组
}


void changeNumber(int *num) {
    *num = 100;
}

struct AndroidBitmapInfo {
    int width;
    int height;
    int format;
};

void AndroidBitmapInfo_getInfo(AndroidBitmapInfo *bitmap_info) {
    bitmap_info->width = 200;
    bitmap_info->height = 300;
}

/**
 * 通过指针间接赋值
 */
void test5() {
    //通过指针修改值，其实是为了在其他方法中取间接赋值
    int a = 10;
    int *p = &a;
    changeNumber(p);

    //在c中，一般是将指针传给其他函数，其他函数操作指针来改值
    //在java中，一般是调用其他方法，其他方法返回结果，在本方法里改值
    AndroidBitmapInfo info;
    AndroidBitmapInfo_getInfo(&info);
    printf("width:%d,height:%d", info.width, info.height);
}

/**
 * 野指针
 */
void test6() {
    //堆上开辟
    AndroidBitmapInfo *androidBitmapInfo = static_cast<AndroidBitmapInfo *>(malloc(sizeof(AndroidBitmapInfo)));
    AndroidBitmapInfo_getInfo(androidBitmapInfo);

    if (androidBitmapInfo != NULL) {
        //free后，地址还在，地址指向的内容没了，就会出现野指针
        free(androidBitmapInfo);
        //置空避免野指针
        androidBitmapInfo = NULL;
    }

    //再次释放
    if (androidBitmapInfo != NULL) {
        free(androidBitmapInfo);
    }
}

/**
 * NULL是什么
 */
void test7() {
    //NULL也是个地方，指针指向NULL相当于指向0x000000
    //但是我们不能对0x000000去操作，这块地方是c和c++编译器持有的
    char *p1 = NULL;
    strcpy(p1, "1111");//报错
}

/**
 * 指针使用的注意事项1
 */
void test8() {
    //犯的错误：在运算过程中不断改变指针位置，但最后要传入的是头指针
    char *name = "abcdefg";
    //正确做法：用临时指针记录头指针
    char *tempName = name;
    for (int i = 0; i < 6; i++) {
        printf("%c", *tempName);
        tempName++;
    }
    printf("\nname:%s", name);
}

/**
 * 指针使用的注意事项2
 */
void malloc1(char **str) {
    //这里改了指针的指向
    *str = "cnting";
}

void test9() {
    char *name = NULL;
    malloc1(&name);

    //这里不会报错
    //指针变量 和 指针所指向的内存变量 是两个不同的概念
    //name存的是NULL的地址，malloc1()里str存的是name的地址
    //malloc1()里改了指针的指向，所以name指向了常量区里的字符串了
    printf("name:%s", name);
}

/**
 * 二级指针的内存模型
 * https://www.bilibili.com/video/BV1Ay4y117HV/?p=72&spm_id_from=pageDriver&vd_source=cfa545ca14ba2d7782dd4c30ae22638e
 */
void printArr(char **strs, int len) {
    for (int i = 0; i < len; i++) {
        printf("%s\n", strs[i]);
    }
}

void printArr1(char strs[][30], int len) {
    for (int i = 0; i < len; i++) {
        printf("%s\n", strs[i]);
    }
}

void test10() {
    //第一种方式
    //这几个数据都是在
    char *name[3] = {"aa", "bb", "cc"};
    printArr(name, 3);

    //第二种方式
    char name1[10][30] = {"ddd", "eeee", "ffff"};
    printArr1(name1, 3);
//    printArr(name1, 3);  //会报错


    //第三种方式（常用）,动态开辟
    int num = 3;
    //开辟二维数组，每个元素存的是一维数组的首地址
    char **params = static_cast<char **>(malloc(sizeof(char *) * num));
    //开辟一维数组
    for (int i = 0; i < num; i++) {
        //一维数组里的每个元素大小为100*char
        params[i] = static_cast<char *>(malloc(sizeof(char) * 100));
        sprintf(params[i], "i = %d", i);
    }
    printArr(params, num);
    //记得释放
    //先释放一维数组
    for (int i = 0; i < num; i++) {
        if (params[i] != NULL) {
            free(params[i]);
            params[i] = NULL;
        }
    }
    //再释放二维数组
    if (params != NULL) {
        free(params);
        params = NULL;
    }
}

/**
 * 多级指针
 */
void initParams1(char **ps) {

}

void initParams2(char ***params, int num) {
    char **tempParams = static_cast<char **>(malloc(sizeof(char *) * num));
    //开辟一维数组
    for (int i = 0; i < num; i++) {
        tempParams[i] = static_cast<char *>(malloc(sizeof(char) * 100));
        sprintf(tempParams[i],"i = %d",i);
    }
    *params = tempParams;
}

void test11() {
    //想在另一个方法里开辟内存
    char **params = NULL;

    //在initParams1()里的ps修改，不会改到params
    initParams1(params);

    //将params的指针传入，initParams2()的改动就会同步到params
    int num = 3;
    initParams2(&params, 3);

    printArr(params, num);
}

int main() {
//    test1();
//    test2();
//    test3();
//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
//    test10();
    test11();
}
