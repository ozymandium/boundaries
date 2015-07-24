#include "boundaries.hpp"

int main(int argc, char** argv) {

  // const char* x = "()";

  Boundary<double, double> b1;
  b1.set(1,2);
  b1.setLower(0);
  b1.setUpper(3);
  std::cout << b1.check(1, "()") << "\n";
  
  return 0;
}