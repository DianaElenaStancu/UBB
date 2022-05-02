cmake_minimum_required(VERSION 3.21)
project(lab10)

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

add_executable(qt_test main.cpp
        domain.cpp domain.h
        exceptions.h
        repository.h
        repository.cpp
        service.h
        service.cpp
        tests.h
        tests.cpp
        ui.h
        ui.cpp
        undo.h
        undo.cpp
        validator.h
        validator.cpp
        gui.h
        gui.cpp
        )
target_link_libraries(qt_test
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

