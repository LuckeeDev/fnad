# Five nights at DIFA
Five nights at DIFA is a 2D game developed for the "Programming for Physics" exam at the University of Bologna.

## Setup guide
We suggest to develop in `Debug` mode, which can be set up with the following command:

```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
```

You can also set CMake in `Release` mode, which increases performance at runtime:

```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
```

Compile and execute the program with CMake:

```bash
$ cmake --build build --target=fnad
$ build/fnad
```

Compile and execute tests with CMake:

```bash
$ cmake --build build --target=all.test
$ build/all.test
```
