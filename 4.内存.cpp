#include <cstdlib>
#include "cstdio"

/**
 * 静态开辟
 */
void staticAllocation() {
    int arr[5];
    int i = 0;
    for (; i < 5; i++) {
        arr[i] = i;
        printf("%d,%p\n", *(arr + i), arr + i);
    }
}

void dynamicAllocation() {
    //动态开辟内存
    int *arr = static_cast<int *>(malloc(10 * 1024 * 1024 * sizeof(int)));  //40M

    //释放内存
    free(arr);
}

void test1() {
    //10M数组大小，int占4字节，所以占40M空间
//    int arr[10 * 1024 * 1024];

    //c有分区
    //栈：占用内存空间最大值：2M，开辟内存的方式是静态内存开辟，方法结束会自动回收
    staticAllocation();
    //堆：占用内存空间最大值：80%，开辟内存的方式是动态内存开辟，不会自动回收（内存不再使用时记得要手动回收）
    dynamicAllocation();
}

/**
 * 实用场景：
 * 假设需要接收用户所输入的数，然后进行排序
 */
void test2() {
    int num;
    printf("请输入数的个数：");
    scanf("%d", &num);

    //不能用静态开辟，内存大小不能改变
//    int arr[num];

    int *arr = static_cast<int *>(malloc(sizeof(int) * num));
    int i = 0;
    int print_num;
    for (; i < num; i++) {
        printf("请输入第%d个的值:", i);
        scanf("%d", &print_num);
        arr[i] = print_num;
    }

    for (i = 0; i < num; i++) {
        printf("%d\n", arr[i]);
    }
    free(arr);
}

/**
 * 改变内存空间大小
 */
void test3() {
    int num;
    printf("请输入数的个数：");
    scanf("%d", &num);

    int *arr = static_cast<int *>(malloc(sizeof(int) * num));
    int i = 0;
    for (; i < num; i++) {
        arr[i] = i;
    }
    printf("开辟内存的指针：%p\n", arr);

    printf("请输入新增的个数：");
    int new_num;
    scanf("%d", &new_num);

    //1.realloc()改变内存大小空间，这个返回值跟上面arr是一个地址，也就是在原地址基础上扩容
    //2.当连续内存不足时，返回的就不是原来的指针，这时候系统会找个新的内存，并把老的数据复制过去，并释放原来的arr
    //3.有时候realloc()会分配失败，此时返回的就是空，所以要判断下
    int *new_arr = static_cast<int *>(realloc(arr, sizeof(int) * (num + new_num)));
    printf("扩容后内存的指针：%p\n", new_arr);

    if (new_arr) {
        //i没重新赋值，接着往下赋值就好
        for (; i < num + new_num; i++) {
            arr[i] = i;
        }

        for (i = 0; i < num + new_num; i++) {
            printf("%d\n", arr[i]);
        }
    }
    //4.释放时也要判断
    //5.也不要反复释放，因为那块地址一旦被释放，可能就被其他应用占用，反复释放会出问题
    if (new_arr) {
        free(new_arr);
        new_arr = NULL;
    } else {
        //到这说明扩容失败，就释放原来地址
        free(arr);
        arr = NULL;
    }
}

int main() {
//    test1();
//    test2();
    test3();
}