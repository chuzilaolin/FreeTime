#include <func.h>


void test() {
    char str[] = "hello world 你好世界";
    FILE *p = fopen("test.txt", "ab+");
    fwrite(str, 1, strlen(str), p);
    fclose(p);
}

void test1() {
    char str[] = "hello world 你好世界";
    FILE *p = fopen("test.txt", "a+");
    fwrite(str, 1, strlen(str), p);
    fclose(p);
}

int main(int argc,char*argv[])
{
    // test();
    test1();
    return 0;
}


