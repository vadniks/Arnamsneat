
file(GLOB DEMO_SOURCES CONFIGURE_DEPENDS src/*.c src/*.h)
add_executable(${DEMO} ${DEMO_SOURCES})
target_include_directories(${DEMO} PRIVATE ../include)
target_link_libraries(${DEMO} ${PROJECT_NAME})
