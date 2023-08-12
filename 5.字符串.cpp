#include "cstdio"
#include "string"

using namespace std;

/**
 * 字符串定义
 */
void test1() {
    //第一种，字符串数组，要以\0结尾
    char str[] = {'a', 'b', 'c', 'd', '\0'};
    printf("%s\n", str);

    //第二种
    char *str2 = "abcd";
    printf("%s\n", str2);

    printf("改变内容\n");
    str[1] = 'y';
//    str2[1] = 'y';   //第二种定义的字符串内容不能改，会报错
    printf("%s\n", str);
    printf("%s\n", str2);
}

/**
 * 字符串长度
 */
int mystrlen(char *str) {
    //这种方式不行
//    int size = sizeof(str) / sizeof(char);

    int size = 0;
    //不断读取字符，判断末尾是\0
    while (*str != '\0') {
        str++;
        size++;
    }

    return size;
}

void test2() {
    char *name = "abcd";
    printf("abcd 长度：%d\n", strlen(name));

    printf("自己计算abcd 长度：%d\n", mystrlen(name));
}

/**
 * 字符串转换
 */
void test3() {
    char *str = "10xxx20";
    printf("10xxx20 转int:%d\n", atoi(str));  //10

    str = "12.5";
    printf("12.5 转int:%d\n", atoi(str));  //12
    printf("12.5 转float:%f\n", atof(str));  //12.500000

    str = "12.5";
    printf("12.5 转double:%lf\n", strtod(str, NULL));

}

/**
 * 字符串比较
 */
void test4() {
    char *str1 = "abcd";
    char *str2 = "abdd";
    printf("%s 和 %s 比较：%d\n", str1, str2, strcmp(str1, str2));

    //不区分大小写
    str1 = "ABC";
    str2 = "abc";
    printf("%s 和 %s 不区分大小写比较：%d\n", str1, str2, strcasecmp(str1, str2));

    //比较前n个
    str1 = "abcc";
    str2 = "abcd";
    printf("%s 和 %s 比较前3个：%d\n", str1, str2, strncmp(str1, str2, 3));

}

/**
 * 查找
 */
void test5() {
    char *str = "Hello World";
    char *substr = "or";
    //得到匹配的位置的指针
    char *pos = strstr(str, substr);
    printf("%s\n", pos);

    //要得到位置
    if (pos) {
        int position = pos - str;
        printf("第一次出现的位置：%d", position);
    } else {
        printf("说明不包含");
    }

}

char *substr(const char *str, int start, int end) {
    //开辟一个字符串存
    int len = end - start;
    char *dest = static_cast<char *>(malloc((len + 1) * sizeof(char))); //这种方式要记得free

    str += start;
    for (int i = 0; i < len; i++) {
        dest[i] = *str;
        str++;
    }
    dest[len] = '\0';
    return dest;
}

void lower(char *dest, char *source) {
    while (*source != '\0') {
        int ch = *source;
        *dest = tolower(ch);
        source++;
        dest++;
    }
    *dest = '\0';
}

/**
 * 拼接、复制、截取、大小写转换
 */
void test6() {
    //复制字符串
    char *str1 = "Hello World";
    char cpy[strlen(str1)];
    strcpy(cpy, str1);
    printf("复制：%s\n", cpy);

    //拼接
    strcat(cpy, str1);
    printf("拼接：%s\n", cpy);

    //截取
    char *sub = substr(str1, 2, 8);
    printf("截取：%s\n", sub);
    free(sub);

    //大小写转换
    char dest[strlen(str1)];
    lower(dest, str1);
    printf("大小写转换：%s\n", dest);
}

/**
 * 字符串替换
 */
char *replace(char *source, char *from, char *to) {
    char *pos = strstr(source, from);
    if (!pos) {
        return source;
    }
    int newArrSize = strlen(source) - strlen(from) + strlen(to);
    char *result = static_cast<char *>(malloc(newArrSize * sizeof(char)));
    int start_end_position = pos - source;
    char *start = substr(source, 0, start_end_position);

    int end_start_position = start_end_position + strlen(from);
    char *end = substr(source, end_start_position, strlen(source));

    strcpy(result, start);
    strcat(result, to);
    strcat(result, end);

    free(start);
    free(end);
    return replace(result, from, to);
}

void test7() {
    char *arr = replace("aabbccaabbcc", "aa", "cc");
    printf("%s", arr);
    free(arr);
}
/**
 * 定义字符串的几种方式的区别
 */
void test8() {
//    char buffer[100] = {'a', 'b', 'c'};//len:3，size:100
//    char buffer[] = {'a', 'b', 'c'}; //len:9，size:3
//    char buffer[100] = {0};  //都初始化为0
//    char buffer[] = "123456";  //len:6，size:7。这种写法相当于 {'1','2','3','4','5','6','\0'}
  char * buffer = "123456";

  //char buffer[] = "123456" 和 char * buffer = "123456" 和 malloc 的区别
  //1.char buffer[]：会从常量区一个个拷贝到栈区的数组各个为止
  //2.char * buffer：直接指向常量区
  //3.malloc：指向堆内存，堆内存里存"123456"
  //所以字符串可以在任何地方开辟内存，栈区、堆区、常量区都可以


    //strlen()碰到'\0'就结束
    int len = strlen(buffer);
    int size = sizeof(buffer);
    printf("len:%d，size:%d\n", len, size);
    //打印内容
    printf("%d，%d，%d\n", buffer[0], buffer[66], buffer[99]);

}

int main() {
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
    test8();
}