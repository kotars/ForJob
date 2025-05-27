cmake_minimum_required(VERSION 3.5)

project(CC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Опции для выбора режимов компиляции
option(DESKTOP "Compile for Desktop" OFF)
option(TETRIS "Compile for Tetris" OFF)
option(SNAKE "Compile for Snake" OFF)
option(CLI "Compile for Command Line Interface" OFF)

# Проверяем допустимые комбинации флагов
if((NOT DESKTOP AND NOT CLI) OR (DESKTOP AND CLI))
    message(FATAL_ERROR "Invalid combination of flags. You must choose either DESKTOP or CLI.")
endif()

# Добавляем макросы в зависимости от выбранных опций
if(DESKTOP)
    add_definitions(-DDESKTOP)
endif()
if(TETRIS)
    add_definitions(-DTETRIS)
endif()
if(SNAKE)
    add_definitions(-DSNAKE)
endif()
if(CLI)
    add_definitions(-DCLI)
endif()

set(PROJECT_SOURCES
        Game/desktop.cpp
        gui/desktop/s21_desktop.h
        brick_game/snake/s21_snake.h
        brick_game/snake/s21_snake.cpp
        brick_game/tetris/s21_tetris.h
        brick_game/tetris/s21_tetris.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CC
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CC APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CC SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CC
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CC PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.CC)
endif()
set_target_properties(CC PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS CC
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CC)
endif()