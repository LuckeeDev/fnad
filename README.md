# Istruzioni

Per impostare CMake in debug mode (consigliata per lo sviluppo):

```bash
$ cmake -B build/debug -S . -DCMAKE_BUILD_TYPE=Debug
```

Per impostare CMake in release mode (N.B: in caso si imposti CMake in release mode, i comandi per la compilazione e l'esecuzione del codice vanno modificati di conseguenza):

```bash
$ cmake -B build/release -S . -DCMAKE_BUILD_TYPE=Release
```

Compilare ed eseguire il programma con CMake:

```bash
$ cmake --build build/debug --target=fnad
$ build/debug/fnad
```

Compilare ed eseguire i test con CMake:

```bash
$ cmake --build build/debug --target=all.test
$ build/debug/all.test
```
