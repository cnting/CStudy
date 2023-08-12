#include <cstring>
#include <cstdlib>
#include "cstdio"

struct Work {
    char name[10];
    char grade[10];
};

struct Worker {
    char name[10];
    int age;
    double salary;
};
//第二种初始化方式，可以有默认初始值
struct Worker2 {
    char name[10];
    int age;
    double salary;
} worker2;  //直接定义名字

struct Worker3 {
    char name[10];
    int age;
    double salary;

    Work work; //可以嵌套
};

/**
 * 结构体初始化
 */
void test1() {
    //第一种初始化方式
    struct Worker worker = {"ct", 11, 100};

    //赋值
    worker.age = 10;
//    worker.name = "aaa";  //这么改会报错，可以用下面这个
    strcpy(worker.name, "aaa");
    printf("name:%s,age:%d,salary:%lf\n", worker.name, worker.age, worker.salary);

    strcpy(worker2.name, "Jack");
    worker2.age = 30;
    printf("name:%s,age:%d,salary:%lf\n", worker2.name, worker2.age, worker2.salary);

    //嵌套结构体
    struct Worker3 worker3 = {"ct", 11, 100, {"Android", "中级"}};
}

/**
 * 结构体指针和动态内存开辟
 */
void test2() {
    //结构体指针
    struct Worker worker = {"ct", 11, 100};
    Worker *worker_p = &worker;
    worker_p->age = 24;
    strcpy(worker_p->name, "Jack");
    printf("name:%s,age:%d,salary:%lf\n", worker_p->name, worker_p->age, worker_p->salary);

    //直接创建结构体指针
    Worker *worker2 = static_cast<Worker *>(malloc(sizeof(Worker)));
    strcpy(worker2->name, "cccc");
    worker2->age = 26;
    printf("name:%s,age:%d,salary:%lf\n", worker2->name, worker2->age, worker2->salary);
    if (worker2) {
        free(worker2);
        worker2 = NULL;
    }
}

/**
 * 结构体数组
 */
void test3() {
    //方式1，静态开辟
    Worker arr[10] = {{"ct", 11, 100},
                      {"cf", 12, 200}};
    arr[9] = {"zz", 70, 500};

    //方式2，动态内存开辟
    Worker *arr2 = static_cast<Worker *>(malloc(sizeof(Worker) * 10));
    //此时指向数组首位置
    strcpy(arr2->name, "aaa");
    arr2->age = 10;
    printf("name:%s,age:%d,salary:%lf\n", arr2->name, arr2->age, arr2->salary);
    //对第10个数据进行操作
    arr2 += 9;
    strcpy(arr2->name, "zzz");
    arr2->age = 9;
    printf("name:%s,age:%d,salary:%lf\n", arr2->name, arr2->age, arr2->salary);

    if (arr2) {
        free(arr2);
        arr2 = nullptr;
    }
}

/**
 * 结构体大小（字节对齐）
 */
struct Worker4 {
    int age; //4字节
    double salary; //8字节
};

struct Worker5 {
    char name[10];  //10字节
    int age; //4字节
    double salary; //8字节

    //共24字节 = 8 * 3
};
struct Worker6 {
    char name[18];  //18字节
    int age; //4字节
    double salary; //8字节

    //共32字节
    //18+4+8=30，不能整除8，往上累加到32能整除
};
struct date {
    int year; //4字节
    int month;//4字节
    int day;  //4字节
};
struct student {
    int number; //4字节
    char sex;   //本来是1字节，但也是占4字节，字节对齐
    int age;    //4字节
    char name[10]; //10字节，10+4+4+4=22 不能被4整除，所以要加到24
    struct date birthday; //12字节

    //
};

void test4() {
    //计算规则：
    //1.按最大的字节去计算
    printf("Worker4 size:%d\n", sizeof(Worker4));  //16

    //2.只会按基本数据类型去算，所以还是按 double * 3
    printf("Worker5 size:%d\n", sizeof(Worker5));  //24

    //3.首先会把所有都加起来，是否能够整除最大属性的字节数（只看基本数据类型），如果不够往上累加，直到能整除
    //18+4+8=30，不能整除8，往上累加到32能整除
    printf("Worker6 size:%d\n", sizeof(Worker6));  //32

    //https://www.bilibili.com/video/BV1Ay4y117HV/?p=76&spm_id_from=pageDriver&vd_source=cfa545ca14ba2d7782dd4c30ae22638e
    //4.嵌套结构体的计算
    //(1)根据每个属性的偏移量计算出来，结构体的大小跟内部位置摆放有关
    //(2)字节对齐，是针对后面这个变量来看的，比如sex就是看age，跟它对齐，所以sex也占4字节

    //使用结构体注意：
    //(1)把最小字节数尽量往后放
    //(2)结构体一旦定义了不要轻易挪到，因为我们只要知道内部任何一个变量的地址，就能知道整个结构体，比如知道了sex的地址，就能加4个偏移量就能得到age了


    printf("Student size:%d\n", sizeof(student));  //36
    student* stu = NULL;
    //内部的偏移量
    printf("Student.number地址的偏移量:%d\n", &(stu->number)); //0
    printf("Student.sex地址的偏移量:%d\n", &(stu->sex));       //4
    printf("Student.age地址的偏移量:%d\n", &(stu->age));       //8
    printf("Student.name地址的偏移量:%d\n", &(stu->name));     //12
    printf("Student.birthday地址的偏移量:%d\n", &(stu->birthday)); //24
}

/**
 * 结构体和结构体指针取别名
 */
typedef Worker Worker_;
//结构体指针取别名
typedef Worker *WorkerP;

void test5() {
    //使用别名
    Worker_ worker = {"ct", 10, 111};
    printf("%s,%d,%d\n", worker.name, worker.age, worker.salary);


    WorkerP worker_p = static_cast<WorkerP>(malloc(sizeof(Worker)));
    strcpy(worker_p->name, "aa");
    worker_p->age = 90;
    worker_p->salary = 1000;
    printf("%s,%d,%d\n", worker_p->name, worker_p->age, worker_p->salary);

}

typedef struct {
    char name[50];
    int age;
} Student;

void test6() {
    Student stu1 = {"ct", 20};
    Student stu2;
    //在c中，= 是内容赋值操作，是把stu1的值赋值给stu2
    stu2 = stu1;
    //相当于是这两行
//    strcpy(stu2.name,stu1.name);
//    stu2.age = stu1.age;

    printf("%s，%d\n", stu2.name, stu2.age);
    printf("%p，%p\n", stu1, stu2);  //打印出来是两个地址
}

typedef struct {
    char *name;
    int age;
} Student1;

/**
 * 结构体套指针，必须要对结构体里的指针进行初始化
 * 指针可以指向任何地址，它的大小永远是4字节
 */
void test7() {
    Student1 stu = {"aa", 1};
    stu.name = "ct";  //将指针指向常量区的字符串，是可以的
//    strcpy(stu.name,"ct");  //会报错，这是往stu.name里拷贝数据"ct"

    //按这种方式可以，此时stu.name指向堆区，是往堆区拷贝"ct"
    stu.name = static_cast<char *>(malloc(100));
    strcpy(stu.name, "ct");

    stu.age = 222;
    printf("%s,%d", stu.name, stu.age);
}

/**
 * 深拷贝与浅拷贝
 */
//浅拷贝
void copyTo(Student1 *from, Student1 *to) {
    *to = *from; //指针的赋值是浅拷贝，所以from和to里的name指向堆区同一个位置
}

void deepCopyTo(Student1 *from, Student1 *to) {
    *to = *from; //指针的赋值是浅拷贝，所以from和to里的name指向堆区同一个位置

    //重新开辟一块内存，值复制
    to->name = static_cast<char *>(malloc(sizeof(100)));
    strcpy(to->name, from->name);
}

void test8() {
    Student1 stu1;
    stu1.name = static_cast<char *>(malloc(100));
    strcpy(stu1.name, "ct");
    stu1.age = 111;

    Student1 stu2;
    //浅拷贝
//    copyTo(&stu1, &stu2);
    //深拷贝
    deepCopyTo(&stu1, &stu2);

    printf("name:%s,age:%d", stu2.name, stu2.age);

    if (stu1.name != NULL) {
        free(stu1.name);
        stu1.name = NULL;
    }
    if (stu2.name != NULL) {
        free(stu2.name);  //浅拷贝时这里报错
        stu2.name = NULL;
    }
}


void test9(){

}
int main() {
//    test1();
//    test2();
//    test3();
    test4();
//    test5();
//    test6();
//    test7();
//    test8();
}