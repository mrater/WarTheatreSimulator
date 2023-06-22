cmake_minimum_required(VERSION 3.13.0)
project("WarTheaterSimulator")
set (CMAKE_CXX_STANDARD 20)
add_compile_options(
    -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG 
    # -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
    
    )
set(SOURCES
    "src/area.cpp"
    "src/battle.cpp"
    "src/field.cpp"
    "src/mapeditor.cpp"
    "src/units.cpp"
    "src/theatrecontroller.cpp"
    "src/utilities.cpp"
)
add_executable(wts ${SOURCES})
add_executable(example1 ${SOURCES} "test/example1.cpp")
target_include_directories(wts PRIVATE "include/")
target_include_directories(example1 PRIVATE "include/")