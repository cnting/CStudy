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
    char sex;   //1字节
    int age;    //4字节
    char name[10]; //10字节
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

    //4.TODO
    printf("Student size:%d\n", sizeof(student));  //36
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

int main() {
//    test1();
//    test2();
//    test3();
//    test4();
    test5();
}