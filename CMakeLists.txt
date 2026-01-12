cmake_minimum_required(VERSION 3.10)
project(3D_Engine)

set(CMAKE_CXX_STANDARD 17)
include_directories(libs/freeglut/include libs/glm src ${CMAKE_SOURCE_DIR})
link_directories(libs/freeglut/lib/x64)

add_executable(Game
    src/main.cpp src/Engine.cpp src/Engine.h
    src/Cube.cpp src/Cube.h src/Primitives.cpp src/Primitives.h
    src/Camera.cpp src/Camera.h src/Observer.cpp src/Observer.h
)

target_link_libraries(Game freeglut opengl32 glu32)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Game>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/crate.jpg" "$<TARGET_FILE_DIR:Game>/assets/crate.jpg"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/crate.jpg" "$<TARGET_FILE_DIR:Game>/crate.jpg"
)