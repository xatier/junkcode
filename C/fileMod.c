/*
this is a program which change "-rwxr-xr-x" like file mod to "755" in octal
written by xatier
*/

#include <stdio.h>

int main (void) {
    int val = 0;
    char mod[12];
    printf("Give me the file mod like \"-rwxr-xr-x\" ->");
    scanf("%s", mod);
    val = ((mod[1]=='r'?4:0) + (mod[2]=='w'?2:0) + (mod[3]=='x'?1:0))*100 +
          ((mod[4]=='r'?4:0) + (mod[5]=='w'?2:0) + (mod[6]=='x'?1:0))*10 +
          ((mod[7]=='r'?4:0) + (mod[8]=='w'?2:0) + (mod[9]=='x'?1:0));
    printf("%s = %d\n", mod, val);
    return 0;
}
