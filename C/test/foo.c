#include <stdio.h>
#include <string.h>

int check (const char *password) {
    int a;
    char buf[8];
    a = strcmp(password, "1234567");
    strcpy(buf, password);
    return a;
}

int main (void) {
    char pswd[1024];
    while (1) {
        scanf("%s", pswd);
        if (check(pswd)) {
            printf("QQ\n");
        }
        else {
            printf("OK!\n");
            break;
        }

    }
    printf("Hello world!");
    return 0;
}
