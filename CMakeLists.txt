cmake_minimum_required(VERSION 3.15)
project(KvStore VERSION 1.0)

# Set C++ standard to C++17 (matching your resume)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define source files
file(GLOB SOURCES "src/*.cpp")

# Create the main executable binary
add_executable(redis_server ${SOURCES})

# Enable threading support (required for multithreading & epoll)
find_package(Threads REQUIRED)
target_link_libraries(redis_server PRIVATE Threads::Threads)