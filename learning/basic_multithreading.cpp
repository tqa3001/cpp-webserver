#include <iostream>
#include <thread>
#include <atomic>

void funct1(char c) { 
  for (int i = 0; i < 10; i++) {
    std::cout << c;
  }
}

void funct2(char c) { funct1(c); }

int main() {
  /* Sequential consistency makes this fully deterministic: */
  std::thread worker1(funct1, 'a');
  std::thread worker2(funct2, 'b');
  worker1.join();
  worker2.join();
  std::atomic<bool> ready(false);
  return 0;
}