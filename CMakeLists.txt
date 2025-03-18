cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES CXX)

set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/clang.exe")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=x86_64-w64-windows-gnu -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   

add_executable(main src/main.cpp)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

# Find SDL2 package
find_package(SDL2 REQUIRED)
# Include SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

# Link SDL2 and SDL2_gfx to your target
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_GFX_LIBRARIES})