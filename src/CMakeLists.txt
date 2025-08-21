set(LIBRARY_NAME ${PROJECT_NAME})
set(LIBRARY_TARGET_NAME "${LIBRARY_NAME}_lib")

add_library(${LIBRARY_TARGET_NAME} STATIC)
target_precompile_headers(${LIBRARY_TARGET_NAME} PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>")

set(HEADERS
        app/application.h

        app/IPresenter.h
        app/IView.h
        app/IModel.h

        app/model_layer.h
        app/presenter_layer.h
        app/tui_layer.h

        utils/threadwrapper.h)

set(SOURCES
        app/application.cpp

        app/model_layer.cpp
        app/presenter_layer.cpp
        app/tui_layer.cpp

        utils/threadwrapper.cpp)

target_sources(${LIBRARY_TARGET_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${LIBRARY_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/app
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        )

find_package(Threads REQUIRED)

target_link_libraries(${LIBRARY_TARGET_NAME}
        PUBLIC
        Threads::Threads
        Infotecs::logger
        )

add_library(Infotecs::main_lib ALIAS ${LIBRARY_TARGET_NAME})