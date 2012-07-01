#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;
int main (void) {
  std::cout << "Hello world" << std::endl;
  int a[5] = {1, 2, 5, 4, 3};
  sort(a, a+5);
  for (int i = 0; i < 5; i++) {
      cout << " " << a[i];
  }

}
