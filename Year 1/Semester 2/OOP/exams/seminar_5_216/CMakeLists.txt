cmake_minimum_required(VERSION 3.21)
project(seminar_example)

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

add_executable(seminar_example main.cpp country.cpp country.h repository.cpp repository.h service.cpp service.h conutry_ui.cpp conutry_ui.h)
target_link_libraries(seminar_example
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

