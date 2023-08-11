#include <cstdio>
#include <cstring>

union Person {
    char name[10];  //10字节
    int age;        //4字节
};

int main() {
    Person person;
    strcpy(person.name,"ct");
    person.age = 20;
    //只有age有值
    printf("name:%s,age:%d\n",person.name,person.age);

    person.age = 20;
    strcpy(person.name,"ct");
    //只有name有值
    printf("name:%s,age:%d\n",person.name,person.age);

    //union只能使用一个字段，所以只找最大字段的值是10，不能被4整除，往上加到12
    printf("%d",sizeof (Person));  //12
}