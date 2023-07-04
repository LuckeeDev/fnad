# Five nights at DIFA
Five nights at DIFA is a 2D game developed for the "Programming for Physics" exam at the University of Bologna. The player is trapped inside the Physics department of the University of Bologna and must find three keys before the timer gets to zero to escape from one of the doors at the top of the map. Be careful: other people in the department are getting sick from a deadly virus and will try to infect you!

You can move the character by pressing <kbd>W</kbd><kbd>A</kbd><kbd>S</kbd><kbd>D</kbd> keys or the <kbd>&#8592;</kbd><kbd>&#8593;</kbd><kbd>&#8594;</kbd><kbd>&#8595;</kbd> arrows.

## Install required packages
Five nights at DIFA requires two external packages: [`SFML`](https://sfml-dev.org) and [`tmxlite`](https://github.com/fallahn/tmxlite). You need to install these packages in order to compile and run the game. `SFML` is available on Ubuntu through the system package manager, so you can install it by running:
```bash
$ sudo apt install libsfml-dev
```
In order to install `tmxlite`, you will need to have `CMake` on your system to manually build the library from its source code. These are the steps you must follow to compile and install it:
```bash
$ git clone https://github.com/fallahn/tmxlite
$ cd tmxlite/tmxlite
$ mkdir build && cd build
$ cmake .. -DTMXLITE_STATIC_LIB=TRUE
$ sudo make install
```

## Compile and run
We suggest to compile in `Debug` mode if you want to develop new features for the game. It can be set up with the following command:

```bash
$ cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
```

Otherwise, you should opt for `Release` mode, which increases performance at runtime:

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
