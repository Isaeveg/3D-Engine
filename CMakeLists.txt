cmake_minimum_required(VERSION 3.10)
project(3D_Engine)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_SOURCE_DIR}/libs/freeglut/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}) 


link_directories(${CMAKE_SOURCE_DIR}/libs/freeglut/lib/x64)

add_executable(Game
    src/main.cpp src/Engine.cpp src/Engine.h
    src/Cube.cpp src/Cube.h src/Pyramid.cpp src/Pyramid.h
    src/Camera.cpp src/Camera.h src/BitmapHandler.cpp src/BitmapHandler.h
)

target_link_libraries(Game freeglut opengl32 glu32)


add_custom_command(TARGET Game POST_BUILD
   
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Game>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/crate.jpg" "$<TARGET_FILE_DIR:Game>/assets/crate.jpg"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/wall.jpg" "$<TARGET_FILE_DIR:Game>/assets/wall.jpg"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/libs/freeglut/bin/x64/freeglut.dll" "$<TARGET_FILE_DIR:Game>/freeglut.dll"
    COMMENT "Kopiowanie zasobow i DLL..."
)