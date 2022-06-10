cmake_minimum_required(VERSION 3.21)
project(simulare_217)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/dianastancu/Qt/6.3.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(simulare_217 main.cpp
        domain.cpp
        domain.h
        repository.cpp
        repository.h
        service.h
        service.cpp
        gui.cpp
        gui.h)
target_link_libraries(simulare_217
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

