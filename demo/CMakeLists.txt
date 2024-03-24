
file(GLOB EXE_DEMO_SOURCES CONFIGURE_DEPENDS src/*.c src/*.h)
add_executable(${EXE_DEMO} ${EXE_DEMO_SOURCES})
target_include_directories(${EXE_DEMO} PRIVATE ../include)
target_link_libraries(${EXE_DEMO} ${PROJECT_NAME})
