cmake_minimum_required(VERSION 3.24)
project(infotecs)

set(CMAKE_CXX_STANDARD 17)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
add_compile_options(-Wall -Wextra -Wpedantic)
find_package(Threads REQUIRED)


# Создание списка файлов для библиотеки логирования
set(LOGGING_SOURCES src/logger.cpp)
set(LOGGING_HEADERS include/logger.h include/log_level.h)

# Основная библиотека
add_library(logging ${LOGGING_SOURCES} ${LOGGING_HEADERS})
target_link_libraries(logging PUBLIC Threads::Threads)


# Настройки для разных типов сборки
if (BUILD_SHARED_LIBS)
    target_compile_definitions(logging PRIVATE LOGGING_BUILDING_DLL)
else ()
    target_compile_definitions(logging PUBLIC LOGGING_STATIC)
endif ()

add_executable(infotecs main.cpp)
target_link_libraries(infotecs PRIVATE logging Threads::Threads)
