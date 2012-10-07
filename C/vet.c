#include <stdio.h> 
#include <string.h>
 
int main (void) { 
    int N;
    scanf("%d", &N);
    getchar();
    char str[100];
    char copy[100];
    int a, b, c, d, i, len;
    while (N--) {
        memset(str, 0, 100);
        fgets(str, 100, stdin);
        len = strlen(str);
        for (i = 1; i <= len; i++) {
            copy[i-1] = str[len-i];
        }
        copy[i] = '\0';
        sscanf(copy, "%d%d", &a, &b);
//printf("%d", a + b);
        sprintf(str, "%d", a + b);

        len = strlen(str);
        for (i = 1; i <= len; i++) {
            copy[i-1] = str[len-i];
        }
        copy[i] = '\0';
        puts(copy);
    }
    return 0; 
} 

