# C++ Multithreading

## Thread
- A smallest unit of execution in a process. 
- Each thread has its some private states, and there's also a global state where all
threads can access. Careful treatment is needed when threads access this global state.
-> Shared data & thread-local data.

## Semaphore
- For limiting access to resources. A semaphore can give out some number of permits, and once it has ran out of
permits, new threads are blocked from requesting the resources until some threads returns permits back to the
semaphore. Bruh C++ has no semaphores.

## Atomic operations
- Operations that can be executed without interruption?

## Memory model: Foundation of multithreading
- Deals with partial ordering of operations and visibility (when shared variables are visible on other threads)
- C++ memory order allows breaking **sequential consistency**.

### The contract (programmer <-> system)
- Stronger contract -> harder to generate optimized code.
- But weaker contract -> lots of optimization options that only a few exports are capable of exploting.
- Strongest (been using so far): Single-thread (sequential consistency, 1 control flow) -> Mid-level: Multithread (threads, tasks, condition variables) -> Weakest: lock-free programming, relax semantic
- C++'s memory model is like Java's memory model with extra rules for dealing with shared variables to obey. It's base are atomics.

### Strong memory model
- With **sequential consistency**:
  + Instructions are executed in source code order \\
    e.g thread(f() {a; b}) => a first then b 
  + Exists a global order for all executions on all threads.
  ALL operations on threads obey a universal clock?
- 

## Critical section
- Some body of code that can be executed by multiple threads and exposes resoruces that can be
access by all of these threads.

## Data races
- Reading and writing a shared mutable variable at the same time is a data race, and therefore, undefined behavior. 
- Coordinating access to a shared variable is achieved with mutexes and locks in C++.

## Mutexes
- "Mutually exclusive" -> Ensure only one thread can access the same critical section at a time. When the thread gets a mutex -> all other threads are block. When that thread releases the mutex -> some heuristics to choose the next thread to hold the mutex.
- C++ has five different mutexes; they can **lock** recursively, tentatively, and with or without time constraints. Even mutexes can share a lock at the same time.

## Locks
- Encapsulate a mutex in a lock to **release it automatically** by binding the mutex's lifetime to the lock's lifetime.
- Lock implements *RAII idiom* (Resource acquisition is initialization).
Wiki: ``` In RAII, holding a resource is a class invariant, and is tied to object lifetime. Resource allocation (or acquisition) is done during object creation (specifically initialization), by the constructor, while resource deallocation (release) is done during object destruction (specifically finalization), by the destructor. ```
- C++: `std::lock_guard`; `std::unique_lock`; `std::shared_lock`

## Thread-safe data initialization
- Multiple ways for read-only data: **constexpr, static variable with block scope, std::call_once + std::once_flag**

## Thread local data
- We can declare data as thread-local -> each thread gets its own copy. 
- Lifetime of thread-local data is bound to the thread's lifetime.

## Condition variables
- Sometimes threads need to be synchronized. 
- This is done with one thread sending messages, one thread receving messages -> bipartite graph.
- Typical: producer-consumer workflow (is it the n - 1 - n one?)
- Easier: Using **tasks**.

## Tasks
- Act like a channel that allows **thread-safe communication between threads**.
- The promise `std::promise` at one endpoint puts data into the data channel, and the future `std::future` at the other endpoint picks the value up. 
- There's `std::async` too.

## STL
- From C++17: STL parallel algorithms, C++11 and C++14 -> building blocks, "assembly" for C++17 multithreading.
- Most STL in C++17 can be parallelized (overloaded), so we need an execution policy. Sequential `std::seq`, in parallel `std::par`, or in parallel with additional vectorization `std::par_unseq`.
