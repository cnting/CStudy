
#include <cstdio>
#include <cstring>
#include <cstdlib>

/**
 * 读文件
 */
void test1() {
    char *fileName = "test.txt";
    //指向头指针
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("文件打开失败");
        return;
    }
    char buffer[10];
    while (fgets(buffer, 10, file)) {
        printf("%s", buffer);
    }
    fclose(file);
}

/**
 * 写文件
 */
void test2() {
    char *fileName = "test.txt";
    FILE *file = fopen(fileName, "w");
    if (!file) {
        printf("文件打开失败");
        return;
    }
    char *content = "写入文件中";
    fputs(content, file);
    fclose(file);
}

/**
 * 文件复制
 */
void test3() {
    FILE *file = fopen("a.jpeg", "rb");
    FILE *file_copy = fopen("copy.jpeg", "wb");
    if (!file || !file_copy) {
        printf("打开文件失败");
        return;
    }
    int buffer[512];
    int len;
    while ((len = fread(buffer, sizeof(int), 512, file)) != 0) {
        fwrite(buffer, sizeof(int), len, file_copy);
    }
    fclose(file_copy);
    fclose(file);
}

long getFileSize(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("打开文件失败");
        return 0;
    }
    //没有函数可以直接拿文件大小
    //实现思路：将文件的指针移动到最后，然后再去计算偏移量

    //1.将指针移动到最后
    //SEEK_SET(开头)、SEEK_CUR(当前)、SEEK_END(最后)
    fseek(file, 0, SEEK_END);
    //2.计算偏移位置，从0开始统计到当前为止
    long len = ftell(file);

    fclose(file);

    return len;
}

/**
 * 获取文件大小
 */
void test4() {
    long len = getFileSize("a.jpeg");
    printf("fileSize:%ld", len);
}

/**
 * 文件加密
 * 思路：
 * 方式1：把每个字节都拿出来，对每个字节都进行处理
 * 方式2：把某部分字节拿出来
 *
 * 加密方式：比如拿出的一个字节是10
 * 方式1.加个值，比如5
 * 方式2.用异或，10^5
 */
void encryptDecryptFile(FILE *from, FILE *to) {
    if (!from || !to) {
        printf("打开文件失败");
        return;
    }
    int c;
    while ((c = fgetc(from)) != EOF) {
        fputc(c ^ 5, to);
    }
}

void test5() {
    FILE *file = fopen("a.jpeg", "rb");
    FILE *file_encrypt = fopen("encrypt.jpeg", "wb");
    encryptDecryptFile(file, file_encrypt);
    fclose(file);
    fclose(file_encrypt);

    //因为是用异或，所以加解密代码一样
    file_encrypt = fopen("encrypt.jpeg", "rb");
    FILE *file_decrypt = fopen("decrypt.jpeg", "wb");
    encryptDecryptFile(file_encrypt, file_decrypt);
    fclose(file_encrypt);
    fclose(file_decrypt);
}

/**
 * 字符串密码加密
 */
void encryptDecryptFile(FILE *from, FILE *to, char *pwd) {
    if (!from || !to) {
        printf("打开文件失败");
        return;
    }
    int c;
    int index;
    int pwdLen = strlen(pwd);
    while ((c = fgetc(from)) != EOF) {
        fputc(c ^ pwd[index % pwdLen], to);
        index++;
    }
}

void test6() {
    char *pwd = "123456";
    FILE *file = fopen("a.jpeg", "rb");
    FILE *file_encrypt = fopen("encrypt.jpeg", "wb");
    encryptDecryptFile(file, file_encrypt, pwd);
    fclose(file);
    fclose(file_encrypt);

    //因为是用异或，所以加解密代码一样
    file_encrypt = fopen("encrypt.jpeg", "rb");
    FILE *file_decrypt = fopen("decrypt.jpeg", "wb");
    encryptDecryptFile(file_encrypt, file_decrypt, pwd);
    fclose(file_encrypt);
    fclose(file_decrypt);
}


/**
 * 文件切割
 */
void split() {
    char *fileName = "a.jpeg";
    FILE *file = fopen(fileName, "rb");
    long file_size = getFileSize(fileName);

    int file_number = 3;
    int preFileSize = file_size / file_number;
    //开辟二维数组
    char **file_names = static_cast<char **>(malloc(sizeof(char *) * file_number));
    //
    for (size_t i = 0; i < file_number; i++) {
        file_names[i] = static_cast<char *>(malloc(sizeof(char) * 30));
        sprintf(file_names[i], "a_%d.jpeg", i);
        printf("%s\n", file_names[i]);
    }
    for (size_t i = 0; i < file_number; i++) {
        FILE *cur_file = fopen(file_names[i], "wb");
        int start = i * preFileSize;
        int end = (i + 1) * preFileSize;
        if (i == file_number - 1) {
            end = file_size;
        }

        for (size_t t = start; t < end; t++) {
            //从file读，写入到cur_file
            fputc(fgetc(file), cur_file);
        }
        fclose(cur_file);
        free(file_names[i]);
    }

    fclose(file);
    free(file_names);
}

void combine() {
    char *files[] = {"a_0.jpeg", "a_1.jpeg", "a_2.jpeg"};
    FILE *combineFile = fopen("combine.jpeg", "wb");
    for (int i = 0; i < 3; i++) {
        FILE *curFile = fopen(files[i], "rb");
        int c;
        while ((c = fgetc(curFile)) != EOF) {
            fputc(c, combineFile);
        }
        fclose(curFile);
    }
    fclose(combineFile);
}

void test7() {
    split();
    combine();
}

int main() {
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
    test7();
}
