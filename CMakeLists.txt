cmake_minimum_required(VERSION 3.16)
project(fnad VERSION 0.0.1)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ./modules)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS
        " -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wcast-qual -Wformat=2"
        " -Wundef -Wshadow -Wcast-align -Wunused -Wnull-dereference"
        " -Wdouble-promotion -Wimplicit-fallthrough -Wextra-semi -Woverloaded-virtual"
        " -Wnon-virtual-dtor -Wold-style-cast")

# abilita address sanitizer e undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

# richiedi il componente graphics della libreria SFML, versione 2.5
# le dipendenze vengono identificate automaticamente
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(tmxlite)

add_executable(fnad main.cpp src/map/map.cpp src/room/room.cpp src/game/game.cpp src/epidemic/epidemic.cpp src/entities/character/character.cpp src/entities/enemy/enemy.cpp src/entities/entity/entity.cpp)
target_link_libraries(fnad PRIVATE sfml-graphics)
target_link_libraries(fnad PRIVATE tmxlite)

# se il testing e' abilitato...
# per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)
    # aggiungi l'eseguibile all.test
    add_executable(all.test test/all.test.cpp)
    target_link_libraries(all.test PRIVATE sfml-graphics)
    target_sources(all.test PRIVATE src/entities/enemy/enemy.test.cpp src/entities/character/character.test.cpp src/epidemic/epidemic.test.cpp)
    target_sources(all.test PRIVATE src/entities/character/character.cpp src/entities/enemy/enemy.cpp src/entities/entity/entity.cpp src/epidemic/epidemic.cpp)
    # aggiungi l'eseguibile all.test alla lista dei test
    add_test(NAME all.test COMMAND all.test)
endif ()
