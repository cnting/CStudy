#include <cstdio>

/**
 * 数组做参数传递，会退化成指针，传递的是首地址（这么做会高效一些）
 */
void print(int arr[]) {
    //这里获取的长度有问题
    int length = sizeof(arr) / sizeof(int);
    printf("只传递数组，在函数中得到的length = %d\n", length);  //2

    printf("错误的打印：\n");
    //只打印了两个
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }

}
//正确做法是要传递length
void print(int arr[],int length) {
    printf("\n正确的打印：\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
}

void test1() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(arr) / sizeof(int);
    printf("size = %d\n", size); //6

    print(arr);
    print(arr,size);
}

int main() {
    test1();
}
