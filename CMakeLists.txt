cmake_minimum_required(VERSION 3.13.0)
project("WarTheaterSimulator")

set(SOURCES
    "src/area.cpp"
    "src/battle.cpp"
    "src/field.cpp"
    "src/main.cpp"
    "src/units.cpp"
)
add_executable(wts ${SOURCES})
target_include_directories(wts PRIVATE "include/")