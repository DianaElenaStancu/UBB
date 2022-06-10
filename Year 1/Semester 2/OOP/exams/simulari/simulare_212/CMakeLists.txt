cmake_minimum_required(VERSION 3.21)
project(simulare_212)

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

add_executable(simulare_212 main.cpp
        domain.h
        domain.cpp
        repository.h
        repository.cpp
        service.cpp
        service.h
        gui.h
        gui.cpp
        validator.h
        validator.cpp)
target_link_libraries(simulare_212
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        )

