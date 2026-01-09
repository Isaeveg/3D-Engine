cmake_minimum_required(VERSION 3.10)
project(3D_Engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(libs/freeglut/include)
include_directories(libs/glm)
include_directories(src)

link_directories(libs/freeglut/lib/x64)

add_executable(Game
    src/main.cpp
    src/Engine.cpp
    src/Engine.h
    src/Observer.cpp
    src/Observer.h
    src/Cube.cpp
    src/Cube.h
    src/Primitives.cpp
    src/Primitives.h
)

target_link_libraries(Game freeglut opengl32 glu32)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${PROJECT_SOURCE_DIR}/libs/freeglut/bin/x64/freeglut.dll"
    $<TARGET_FILE_DIR:Game>
)