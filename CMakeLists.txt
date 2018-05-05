cmake_minimum_required(VERSION 2.8)
#SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
project(Cross)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5  COMPONENTS  Widgets REQUIRED)
add_executable(${PROJECT_NAME} main.cpp
    Cross.h Cross.cpp
    ActionSlider.cpp ActionSlider.h
    ActionCheckBox.cpp ActionCheckBox.h
)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets )
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
