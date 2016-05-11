cmake_minimum_required(VERSION 2.8.11)

project(testproject)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

############ OpenCV PACKAGE #########
set(BUILD_SHARED_LIBS ON)
set(OpenCV_FIND_QUIETLY FALSE)
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Find the QtWidgets library
find_package(Qt5Widgets)
qt5_wrap_cpp(tcp_hdr_moc ${PROJECT_SOURCE_DIR}/TcpServer.h)
# Tell CMake to create the helloworld executable
add_executable(helloworld WIN32 main.cpp
    TcpServer.h TcpServer.cpp
    )
# Use the Widgets module from Qt 5.
target_link_libraries(helloworld Qt5::Widgets
    ${OpenCV_LIBS}
    ${PROJECT_SOURCE_DIR}/TcpServer.cpp
    ${PROJECT_SOURCE_DIR}/TcpServer.h
    )
