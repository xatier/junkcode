#include <iostream>

class foo {
public:
    foo(void) : qq(10) {std::cout << "foo constructed" << qq << std::endl;}
    ~foo(void) {std::cout << "foo destructed" << std::endl;}
private:
    int qq;
};

int main () {
    foo *a = new foo();

}
