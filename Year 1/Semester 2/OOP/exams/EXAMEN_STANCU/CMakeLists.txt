cmake_minimum_required(VERSION 3.22)
project(EXAMEN_STANCU)

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

add_executable(EXAMEN_STANCU main.cpp
        service.cpp
        service.h
        observer.h
        observer.cpp
        domain.h
        domain.cpp
        repository.cpp
        repository.h
        ui.cpp
        ui.h
        closeW.cpp
        closeW.h
        inProgressW.cpp
        inProgressW.h
        openW.cpp
        openW.h
        )
target_link_libraries(EXAMEN_STANCU
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

