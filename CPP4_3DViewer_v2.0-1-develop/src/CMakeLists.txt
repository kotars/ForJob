cmake_minimum_required(VERSION 3.22)

project(
    3DViewer_v2
    VERSION 2.0
)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(utils)

file(COPY ${CMAKE_SOURCE_DIR}/obj_files/ DESTINATION ${CMAKE_BINARY_DIR}/obj_files)

include_directories("include")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(BUILD_SHARED_LIBS YES)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


if(WIN32)
    add_compile_options(/permissive-)
endif()



# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)

# LIBS
if(WIN32)
    # find_package(Qt6 )
    # find_package(OpenGL REQUIRED)
    # SET(DESKTOP_LIB qt::qt OpenGL::GL OpenGL::GLU)
    find_package(OpenGL REQUIRED)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL)
    SET(DESKTOP_LIB             Qt6::Core Qt6::Gui OpenGL::GL OpenGL::GLU Qt6::OpenGLWidgets Qt6::Widgets)
    SET(MAIN_LIB ${MAIN_LIB}    Qt6::Core Qt6::Gui OpenGL::GL OpenGL::GLU Qt6::OpenGLWidgets Qt6::Widgets Qt6::OpenGL)
    
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    include_directories(${Qt6Widgets_INCLUDE_DIRS})
    include_directories(${Qt6OpenGL_INCLUDE_DIRS})
elseif(UNIX)
    find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets )
    find_package(OpenGL REQUIRED)
    SET(DESKTOP_LIB Qt6::Widgets Qt6::Core Qt6::Gui Qt6::OpenGL OpenGL::GL OpenGL::GLU Qt6::OpenGLWidgets)
    SET(MAIN_LIB ${MAIN_LIB} Qt6::Core Qt6::Gui OpenGL::GL OpenGL::GLU Qt6::OpenGLWidgets Qt6::Widgets Qt6::OpenGL)
    include_directories(${Qt6OpenGL_INCLUDE_DIRS})
endif()




SET(MAIN_LIB ${MAIN_LIB} Qt6::OpenGL)
SET(TEST_LIB ${MAIN_LIB} Qt6::Core core_test )


# FLAGS
SET(MAIN_FLAGS -Wall)
IF(UNIX)
    SET(MAIN_FLAGS ${MAIN_FLAGS} -Wextra)
endif()

SET(TEST_FLAGS ${MAIN_FLAGS} -fprofile-arcs -ftest-coverage)

message(
    STATUS
    "FLAGS
  MAIN_FLAGS        : ${MAIN_FLAGS}
  TEST_FLAGS        : ${TEST_FLAGS}
    "
)


# FILES
# file(GLOB_RECURSE TETRIS_LOGICAL_FILES "brick_game/tetris/*.c")
file(GLOB_RECURSE CORE_FILES "core/*.cpp")
file(GLOB_RECURSE MODEL_FILES "model/*.cpp")
file(GLOB_RECURSE CONTROLLER_FILES "controller/*.cpp")

file(GLOB_RECURSE DESKTOP_FILES "gui/*.cpp" "gui/*.ui")

# file(GLOB_RECURSE CONTROL_FILES "control/main.cpp")



####################################
# add_subdirectory(third_party/QtGifImage)

create_library(core FILES ${CORE_FILES} FLAGS ${MAIN_FLAGS} LIBS ${MAIN_LIB} )
create_library(model FILES ${MODEL_FILES} FLAGS ${MAIN_FLAGS} LIBS ${MAIN_LIB} core)
create_library(controller FILES ${CONTROLLER_FILES} FLAGS ${MAIN_FLAGS} LIBS ${MAIN_LIB} model)
create_library(core_test FILES ${CORE_FILES} FLAGS ${MAIN_FLAGS} -fprofile-arcs -ftest-coverage -g LIBS ${MAIN_LIB}  -lsubunit -pthread -lgcov )


# include_directories(${PROJECT_NAME} "./third_party/QtGifImage/include/")
create_target(${PROJECT_NAME} FILES ${DESKTOP_FILES} FLAGS ${MAIN_FLAGS} LIBS ${DESKTOP_LIB} core model controller)
# create_target(${PROJECT_NAME} FILES ${DESKTOP_FILES} FLAGS ${MAIN_FLAGS} LIBS ${DESKTOP_LIB} QtGifImage::QtGifImage core model controller)

# create_target(s21_BrickGame FILES ${CONTROL_FILES} ${MOC_SOURCES} ${UI_HEADERS}  FLAGS ${MAIN_FLAGS} LIBS ${MAIN_LIB} tetris snake cli desktop)

add_subdirectory("test")

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            # "$<TARGET_FILE:QtGifImage>"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    # set(QT_DLL_DIR ${CMAKE_BINARY_DIR}/conan)

    # set(QT_DLLS
    #     Qt6OpenGLWidgetsd.dll
    #     Qt6Widgetsd.dll
    #     Qt6Guid.dll
    # )

endif()