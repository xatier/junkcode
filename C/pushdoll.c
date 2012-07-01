#include <stdio.h>

int main (void) {
    char str[80];
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    gets(str);
    printf("%%1\n%s\n\n", str);
    while (gets(str) != NULL) {
        printf("%%5\n%s\n\n", str);
    }
    return 0;
}
