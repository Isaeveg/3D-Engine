cmake_minimum_required(VERSION 3.10)

# Название проекта
project("3D-Engine")

# Используем современный C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === НАСТРОЙКА БИБЛИОТЕК (LIBS) ===

# 1. GLM (Header-only)
# Указываем папку, в которой лежит папка "glm"
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)

# 2. FreeGLUT
# Заголовки (.h)
include_directories(${CMAKE_SOURCE_DIR}/libs/freeglut/include)

# Библиотеки (.lib / .a)
# ВНИМАНИЕ: Если у вас нет папки x64 внутри lib, уберите "/x64" из строки ниже
link_directories(${CMAKE_SOURCE_DIR}/libs/freeglut/lib/x64) 

# === СБОРКА ПРОЕКТА (SRC) ===

# Находим все исходники в папке src
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

# Создаем исполняемый файл Game.exe
add_executable(Game ${SOURCES})

# Добавляем папку src в пути поиска заголовков (чтобы Engine.h виделся в main.cpp)
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/src)

# === ЛИНКОВКА ===

# Подключаем библиотеки к exe-файлу
# freeglut - наша скачанная библиотека
# opengl32, glu32 - системные библиотеки Windows (устанавливать не надо, они есть всегда)
target_link_libraries(Game freeglut opengl32 glu32)

# === КОПИРОВАНИЕ DLL ===

# После сборки копируем freeglut.dll рядом с Game.exe, иначе игра не запустится.
# ВНИМАНИЕ: Проверьте путь. Если dll лежит прямо в bin, уберите "/x64"
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/libs/freeglut/bin/x64/freeglut.dll"
    "$<TARGET_FILE_DIR:Game>")