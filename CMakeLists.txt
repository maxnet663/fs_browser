cmake_minimum_required(VERSION 3.26)
project(fs_browser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/interface)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(fs_browser
        main.cpp
        include/mainwindow.h src/mainwindow.cpp
        include/searcher.h src/searcher.cpp)

target_include_directories(fs_browser PRIVATE ${CMAKE_SOURCE_DIR})

target_link_libraries(fs_browser
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)

