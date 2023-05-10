#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
#include <ctime>
#include <cmath>

void funct1(int val) {
  int counter = 0;
  for (int i = 0; i < 10000000; i++) {
    counter += sqrt(val);
  }
}

void with_multithread(int thread_num) {
  double startTime = 1.0 * clock() / CLOCKS_PER_SEC; 
  std::vector<std::thread> thread_pool;
  for (int i = 0; i < thread_num; i++) {
    thread_pool.emplace_back(funct1, 10);
  }
  for (auto& thread : thread_pool) {
    thread.join();
  }
  double endTime = 1.0 * clock() / CLOCKS_PER_SEC;
  std::cout << "\nExecution time: " << endTime - startTime << "\n";
}

void without_multithread(int thread_num) {
  double startTime = 1.0 * clock() / CLOCKS_PER_SEC; 
  for (int i = 0; i < thread_num; i++)  {
    funct1(10);
  }
  double endTime = 1.0 * clock() / CLOCKS_PER_SEC;
  std::cout << "\nExecution time: " << endTime - startTime << "\n";
}

void memory_model() {
  std::atomic<int> atomic_bool(0);
  atomic_bool.store(4, std::memory_order_seq_cst);  /* sequential consistency */
}

int main() {
  with_multithread(10);
  // without_multithread(10);
  memory_model();
  return 0;
}