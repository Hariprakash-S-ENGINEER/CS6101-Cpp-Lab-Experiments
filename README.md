# CS6101 C++ Lab Experiments (1-10)

A collection of standalone C++ programs based on experiments 1-10 in the CS6101 Object Oriented Programming using C++ lab manual.

## Experiments

1. University management system: encapsulation, constructors, destructors
2. Runtime polymorphism: virtual functions and abstract classes
3. Matrix operations: operator overloading
4. Generic stack and queue: templates and STL timing comparison
5. Student grade analyzer: STL algorithms and lambdas
6. Resource management: RAII, `unique_ptr`, and `shared_ptr`
7. Bank account exception safety: custom exceptions and strong guarantee
8. Move semantics and perfect forwarding for a resource-heavy string
9. Singleton, Factory, and Observer patterns for notifications
10. Multi-threaded producer-consumer system

Each experiment folder contains `main.cpp` and a separate `output.txt` sample.

## Build and run

Each folder contains an independent program. With a C++17 compiler such as `g++`:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic experiment-08/main.cpp -o experiment
./experiment
```

Replace `experiment-08` with the folder you want to run. On Windows, run `experiment.exe` after compiling.

Experiments 4 and 8 report measured timings, which vary by machine, compiler, and system load. Experiment 10 is multi-threaded, so the order of produced and consumed lines may vary between runs. Output files show sample runs.

## Source

Based on experiments 1-10 from `LABMANUALCS6101.pdf`, supplied for this project. The solutions have been organized as separate, readable programs. No student name, register number, or filled-in personal details are included.
