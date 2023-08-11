#include <cstdio>

enum CommentType {
    TEXT = 10, TEXT_IMG = 20, IMG = 30
};

int main() {
    CommentType type = TEXT;
    CommentType type1 = TEXT_IMG;
    CommentType type2 = IMG;

    //枚举在C里是int
    printf("%d,%d,%d,", type, type1, type2);
}
