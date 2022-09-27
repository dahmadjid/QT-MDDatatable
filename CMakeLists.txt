cmake_minimum_required(VERSION 3.16)

project(QRScanner VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-fuse-ld=lld")
if (WIN32)
    add_compile_definitions(WINDOWS)
else()
    add_compile_definitions(LINUX)
    add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address )
endif()

add_link_options(-fsanitize=address)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_subdirectory(src)
# add_subdirectory(libs)