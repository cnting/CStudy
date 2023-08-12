#include <cstdio>
#include <cstdlib>

/**
 * 如何设计一个获取Bitmap属性的函数
 * 1.确定你的参数，传递指针
 * 2.一定要考虑健壮性
 * 3.要把异常错误进行抛出说明
 * 4.不要直接轻易改变调用者传给你的指针，用const修饰
 */

struct AndroidBitmapInfo {
    int width;
    int height;
    int format;
};

int AndroidBitmapInfo_getInfo(AndroidBitmapInfo *bitmap_info) {

    //考虑健壮性
    if (bitmap_info == NULL) {
        //3.异常说明
        printf("bitmapInfo是NULL无法进行操作，错误码:%d\n", -1);
        return -1;
    }
    bitmap_info->width = 200;
    bitmap_info->height = 300;
    return 0;
}

void test1() {
    AndroidBitmapInfo *info = static_cast<AndroidBitmapInfo *>(malloc(sizeof(AndroidBitmapInfo)));

    if (info != NULL) {
        free(info);
        info = NULL;
    }

    //假设释放后再调用
    int res = AndroidBitmapInfo_getInfo(info);
    if (res == 0) {
        printf("width:%d,height:%d", info->width, info->height);
    } else {
        printf("错误了");
    }
}

//传入的指针最好加上const关键字
int strlen(char * const str) {
    int count = 0;
    //不要这样写！！！
//    while (*str != '\0') {
//        count++;
//        str++; //不要直接改传入的指针
//    }

    //要定义临时变量
    char *countStr = str;
    while (*countStr) {
        count++;
        countStr++;
    }

    printf("str:%s，len:%d\n", str, count);
    return count;
}

void test2() {
    char *str = "123456";
    int len = strlen(str);
    printf("len=%d", len);
}

int main() {
//    test1();
    test2();
}