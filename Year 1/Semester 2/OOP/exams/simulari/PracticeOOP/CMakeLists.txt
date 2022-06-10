cmake_minimum_required(VERSION 3.21)
project(PracticeOOP)

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

add_executable(PracticeOOP main.cpp
        domain.cpp
        domain.h
        test_domain.cpp
        test_domain.h
        repository.cpp
        repository.h
        exception.cpp
        exception.h
        test_repo.cpp
        test_repo.h
        service.cpp
        service.h
        validator.cpp
        validator.h
        test_validator.cpp
        test_validator.h
        test_service.cpp
        test_service.h
        gui.cpp
        gui.h
        GuiFilter.cpp
        GuiFilter.h
        undo.cpp
        undo.h
        repofile.cpp
        repofile.h
        test_repofile.cpp
        test_repofile.h)
target_link_libraries(PracticeOOP
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

