#include <iostream>
#include <atomic>
#include <thread>

/* Spinlock: a lock that causes a thread trying to acquire it to 
  simply wait in a loop ("spin") while repeatedly checking whether the lock is available. 
  Since the thread remains active but is not performing a useful task, the use 
  of such a lock is a kind of busy waiting. */
class Spinlock {
public:
  Spinlock() : flag(ATOMIC_FLAG_INIT) {}
  void lock() { while (flag.test_and_set()); }
  void unlock() { flag.clear(); }
private:
  std::atomic_flag flag;
} spin;

/* What if you replace spin with a std::mutex (which also implements lock() and unlock())? 
  Spinlock -> spinning the while loop -> busy waiting, still utilizing CPU 
  Mutex -> passive waiting */

void useResources(char c) {
  /* Notice how read + write are in a same atomic operation. 
    This is crucial in avoiding data races. */
  spin.lock();
  std::cout << c << " using resources\n";
  spin.unlock();
} 

int main() {
  std::thread a(useResources, 'a');
  std::thread b(useResources, 'b');
  a.join();
  b.join();
  return 0;
}
