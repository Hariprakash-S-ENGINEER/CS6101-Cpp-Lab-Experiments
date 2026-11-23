# CS6101 C++ Lab Experiments (1-7)

A collection of standalone C++ programs based on the first seven experiments in the CS6101 Object Oriented Programming using C++ lab manual.

## Experiments

1. University management system: encapsulation, constructors, destructors
2. Runtime polymorphism: virtual functions and abstract classes
3. Matrix operations: operator overloading
4. Generic stack and queue: templates and STL timing comparison
5. Student grade analyzer: STL algorithms and lambdas
6. Resource management: RAII, `unique_ptr`, and `shared_ptr`
7. Bank account exception safety: custom exceptions and strong guarantee

## Build and run

Each folder contains an independent program. With a C++17 compiler such as `g++`:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic experiment-01/main.cpp -o experiment
./experiment
```

Replace `experiment-01` with the folder you want to run. On Windows, run `experiment.exe` after compiling.

Experiment 4 reports measured timings. These vary by machine, compiler, and system load; they are illustrative and should not be treated as a benchmark conclusion.

## Source

Based on experiments 1-7 from `LABMANUALCS6101.pdf`, supplied for this project. The solutions have been organized as separate, readable programs. No student name, register number, or filled-in personal details are included.
