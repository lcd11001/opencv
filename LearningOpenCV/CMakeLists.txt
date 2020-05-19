cmake_minimum_required(VERSION 3.0.0)
project(TestOpenCV VERSION 0.1.0)

find_package(OpenCV REQUIRED)

file(GLOB ALL_SRC
    "LearningOpenCV/*.h"
    "LearningOpenCV/*.cpp"
)
add_executable(${PROJECT_NAME} "${ALL_SRC}")

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
