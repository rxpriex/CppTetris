cmake_minimum_required(VERSION 3.10)
project(main LANGUAGES CXX)

# Set the C++ compiler (clang++ instead of clang for C++ projects)
set(CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/clang++.exe")
set(CMAKE_C_COMPILER "C:/msys64/mingw64/bin/clang.exe")

# Set compiler flags for C and C++ (use CXX_FLAGS for C++ projects)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=x86_64-w64-windows-gnu -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=x86_64-w64-windows-gnu -g")

# Enable compile commands for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add your executable (use ${PROJECT_NAME} consistently)
add_executable(${PROJECT_NAME} src/main.cpp src/Graphics/RxFrame.cpp src/Graphics/Component/RxComponent.cpp)

# Set output directory for the executable
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/out")

# Set the prefix path to prefer MSYS2's MinGW-w64 libraries
set(CMAKE_PREFIX_PATH "C:/msys64/mingw64" ${CMAKE_PREFIX_PATH})

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Include directories for SDL2 and SDL2_gfx (only if found)
include_directories(${SDL2_INCLUDE_DIRS})

# Link SDL2 and SDL2_gfx to your target (only if SDL2_gfx is found)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Set C++ standard explicitly
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)