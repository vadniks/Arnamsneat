
cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_COMPILER /usr/bin/clang)
project(Arnamsneat LANGUAGES C VERSION 1.0)

set(CMAKE_C_STANDARD 23)

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")
add_compile_options("-O3")
add_compile_options("-fvisibility=hidden")

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c src/*.h)
file(GLOB INCLUDES CONFIGURE_DEPENDS include/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})

target_link_libraries(${PROJECT_NAME} SDL2 GL GLEW)
target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${INCLUDES})

set(EXE_DEMO exeDemo)
add_subdirectory(demo)
