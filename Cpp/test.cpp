#include <iostream>
#include <ctime>

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
    delete bar;
    int a = 10;
    ++++++++a;
    std::cout << a;
    std::cout << time(nullptr);

    return 0;
}
