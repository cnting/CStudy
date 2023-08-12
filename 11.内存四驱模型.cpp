
/**
 * https://www.bilibili.com/video/BV1Ay4y117HV/?p=65&spm_id_from=pageDriver&vd_source=cfa545ca14ba2d7782dd4c30ae22638e
 * 程序运行流程：
 * 1.操作系统会把物理硬盘上的代码load到内存
 * 2.加载到内存后，会把c代码分成四个区
 * 3.系统会找到main()的入口去执行
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>

/**
 * 四驱模型：
 * 1.栈区：由编译器自动分配，存放一些局部变量和函数，这个地方的内存是会自动回收的
 * 2.堆区：一般由我们自己开辟的，需要手动进行释放
 * 3.全局区（静态区）：存放静态常量，字符串
 * 4.程序代码区：存放函数体的二进制代码
 */


char *getStr1() {
    //"12345"存放在全局区，返回的是全局区里的地址
    char *str = "12345";
    return str;
}

char *getStr2() {
    char *str = "12345";
    return str;
}

char *getStr3() {
    //存在栈区，返回存在栈区里的地址，这个地址在这个方法结束后会被释放，所以会得不到数据
    //但按C++视频里的说法，是会保留一小会儿再释放
    char buffer[128];
    strcpy(buffer, "12345");
    return buffer;
}

char *getStr4() {
    //存在堆区
    //char * 是四字节的数据类型，存的是堆区开辟的128字节的首地址
    char *buffer = static_cast<char *>(malloc(128));
    strcpy(buffer, "12345");
    return buffer;
}

void test1() {
    char *str1;
    char *str2;
    str1 = getStr1();
    str2 = getStr2();
    //打印出两个首地址是一样的，因为"12345"这个字符串在全局区
    printf("%d,%d\n", str1, str2);

    char *str3 = getStr3();
    //打印：172421022,172421022,-445038384,12345
    //这里很奇怪，str3没有被回收，值还在。跟视频里讲的结果不一样（https://www.bilibili.com/video/BV1Ay4y117HV/?p=65&spm_id_from=pageDriver&vd_source=cfa545ca14ba2d7782dd4c30ae22638e）
    //按C++的视频讲的，是会被回收，但结果会保留一会，等会会被回收（https://www.bilibili.com/video/BV1et411b73Z?p=86&vd_source=cfa545ca14ba2d7782dd4c30ae22638e）
    printf("%d,%d,%s\n", str1, str2, str3);

    char *str4 = getStr4();
    //但到这里的时候str3被回收了，str3打印是乱码
    //53084048,53084048,�0���,12345
    printf("%d,%d,%s,%s\n", str1, str2, str3, str4);
}

void change1(int number) {
    number = 300;
    printf("在change1()中地址：%p\n", &number);
}

void change2(int *number) {
    *number = 400;
}
/**
 * https://www.bilibili.com/video/BV1Ay4y117HV/?p=66&spm_id_from=pageDriver&vd_source=cfa545ca14ba2d7782dd4c30ae22638e
 */
void test2() {
    int a = 100;
    printf("a的地址：%p\n", &a);

    a = 200;

    //值没改，是把a变量的值复制给了number变量，number是一个新的变量
    change1(a);
    printf("a=%d\n", a);  //200

    //传地址能修改值，是把a的地址复制给了number变量，number是一个新的变量
    change2(&a);
    printf("a=%d\n", a);  //400
}

int main() {
//    test1();
    test2();
}
