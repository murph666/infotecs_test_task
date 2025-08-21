find_package(Threads REQUIRED)

set(LOGGER_SOURCES src/logger.cpp)
set(LOGGER_HEADERS
        include/logger.h
        include/log_level.h
        )

add_library(logger ${LOGGER_SOURCES})
target_sources(logger PRIVATE ${LOGGER_SOURCES} ${LOGGER_HEADERS})

target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(logger PUBLIC Threads::Threads)

target_compile_features(logger PUBLIC cxx_std_17)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(logger PRIVATE LOGGING_BUILDING_DLL)
else ()
    target_compile_definitions(logger PUBLIC LOGGING_STATIC)
endif ()

add_library(Infotecs::logger ALIAS logger)