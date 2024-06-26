
cmake_minimum_required(VERSION 3.26)
set(CMAKE_C_COMPILER /usr/bin/clang)
project(Arnamsneat LANGUAGES C VERSION 1.0)

set(CMAKE_C_STANDARD 23)

add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wpedantic")
add_compile_options("-O3")
add_compile_options("-fvisibility=hidden")

if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
    add_compile_options("-Wno-nullability-extension")
endif()

#add_link_options("-s")

file(GLOB SOURCES CONFIGURE_DEPENDS include/arnamsneat/*.h src/*.c src/*.h)
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${INCLUDES})

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_ttf SDL2_image)
target_include_directories(${PROJECT_NAME} PRIVATE include)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set(DEMO demo)
add_subdirectory(${DEMO})

file(COPY ${DEMO}/res DESTINATION ${CMAKE_BINARY_DIR}/demo)
