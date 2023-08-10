#include "stdio.h"
int main(){
    int i = 100;
    double d = 200;
    float f = 200;
    long l = 100;
    short s = 100;
    char c = 'D';

    printf("i的值是:%d\n",i);
    printf("d的值是:%lf\n",d);
    printf("f的值是:%f\n",f);
    printf("l的值是:%ld\n",l);
    printf("s的值是:%d\n",s);
    printf("c的值是:%c\n",c);

    //sizeof() 获取类型所占字节数
    printf("int所占字节数：%lu\n",sizeof(int));
    printf("double：%lu\n",sizeof(double));
    printf("char：%lu\n",sizeof(char));
}
