cmake_minimum_required(VERSION 3.13.0)
project("WarTheaterSimulator")

add_compile_options(
    -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG 
    # -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
    
    )
set(SOURCES
    "src/area.cpp"
    "src/battle.cpp"
    "src/field.cpp"
    "src/main.cpp"
    "src/mapeditor.cpp"
    "src/units.cpp"
    "src/theatrecontroller.cpp"
)
add_executable(wts ${SOURCES})
target_include_directories(wts PRIVATE "include/")