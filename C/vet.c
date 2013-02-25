#include <stdio.h> 
 
void p() {putchar('Q'); p();}

int main (void) { 
    p();
    return 0; 
} 

