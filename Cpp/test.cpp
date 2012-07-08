#include <iostream>

struct foo {
    int bar;
};

void funcc (foo f) {
    std::cout << f.bar;
}

int main (void) {
    foo *bar = new (foo);
    bar->bar = 20;
    funcc(*bar);

    return 0;
}
