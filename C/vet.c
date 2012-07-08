#include <stdio.h>
#include <stdlib.h>

struct foo {
    int bar;
};

void func (struct foo* f) {
    printf("%d", f->bar);
}

void funcc (struct foo f) {
    printf("%d", f.bar);
}

int main (void) {
    struct foo fuu;
    fuu.bar = 10;
    func(&fuu);
    struct foo *bar = (struct foo *)malloc (sizeof(struct foo));
    bar->bar = 20;
    funcc(*bar);
    struct foo zz = (struct foo)bar;
    
    return 0;
}
