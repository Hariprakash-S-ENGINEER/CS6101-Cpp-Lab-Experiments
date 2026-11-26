# CS6101 C++ Lab Experiments (1-13)

Standalone C++ programs based on experiments 1-13 from the CS6101 Object Oriented Programming using C++ lab manual.

## Experiments

1. University management system: encapsulation, constructors, destructors
2. Runtime polymorphism: virtual functions and abstract classes
3. Matrix operations: operator overloading
4. Generic stack and queue: templates and STL timing comparison
5. Student grade analyzer: STL algorithms and lambdas
6. Resource management: RAII, \`unique_ptr\`, and \`shared_ptr\`
7. Bank account exception safety: custom exceptions and strong guarantee
8. Move semantics and perfect forwarding for a resource-heavy string
9. Singleton, Factory, and Observer patterns for notifications
10. Multi-threaded producer-consumer system
11. Type-safe unit conversions using templates and \`constexpr\`
12. Mini file system using file I/O and binary serialization
13. Generic data pipeline using C++20 modules, concepts, and ranges

Each experiment folder contains its program and a separate \`output.txt\` sample. Experiment 13 has a module interface and CMake build file in addition to \`main.cpp\`.

## Build and run

For experiments 1-12, use a C++17 compiler such as \`g++\`:

\`\`\`sh
g++ -std=c++17 -Wall -Wextra -pedantic experiment-11/main.cpp -o experiment
./experiment
\`\`\`

Replace \`experiment-11\` with the folder you want to run. Experiment 4 and Experiment 8 timings vary by computer and compiler. Experiment 10 is multi-threaded, so its line order may vary.

Experiment 13 requires a C++20 compiler with module support and CMake 3.28 or newer:

\`\`\`sh
cmake -S experiment-13 -B build
cmake --build build
\`\`\`

Experiment 12 stores binary records in \`filesystem.dat\` in the program's working directory. The output file shows a sample session starting without existing records.

## Source

Based on experiments 1-13 from \`LABMANUALCS6101.pdf\`, supplied for this project. The programs are organized separately and omit personal student details.
