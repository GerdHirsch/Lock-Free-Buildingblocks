cmake_minimum_required(VERSION 3.20)

# Header only library (INTERFACE) exporting only the include path
add_library(basic_building_blocks INTERFACE)
target_include_directories(
    basic_building_blocks
    INTERFACE include/
)

# Static/Dynamic library depending on header only lib
add_library(
    basic_building_blocks_demo
    src/DemoABASafeIndex.cpp
    src/DemoCalculateHelper.cpp
    src/DemoOther.cpp
    src/DemoRingbufferPosition.cpp
    src/DemoSPSCWaitFreeQueue.cpp
    src/DemoTypeBuilder.cpp
    src/DemoUniqueIndex.cpp
    src/DemoCacheLineCell.cpp
)
target_include_directories(
    basic_building_blocks_demo
    PUBLIC src/
)
target_link_libraries(
    basic_building_blocks_demo
    basic_building_blocks
    pthread
)

# Executable depending on demo lib
add_executable(
    basic_building_blocks_app
    src/main.cpp
)
target_link_libraries(basic_building_blocks_app basic_building_blocks_demo)
