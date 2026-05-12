cmake_minimum_required(VERSION 3.16)

project(waterly VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()   # включает CMAKE_AUTOMOC, AUTOUIC, AUTORCC

set(SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    waterscreen.cpp
    waterscreen.h
    calendarscreen.cpp
    calendarscreen.h
    waterscreen.ui
    calendarscreen.ui
)


qt_add_executable(waterly
    MANUAL_FINALIZATION
    ${SOURCES}
    waterglasswidget.h waterglasswidget.cpp
)

target_include_directories(waterly PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(waterly PRIVATE Qt6::Widgets)

qt_finalize_executable(waterly)
