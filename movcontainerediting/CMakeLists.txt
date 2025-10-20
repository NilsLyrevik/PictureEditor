set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.10)
project(MovFrameExtractor)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to find OpenCV in /usr/local
set(OpenCV_DIR /usr/local/lib/cmake/opencv4)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#Recursive file stuff
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(main 
    main.cpp 
    ${SRC_FILES}
    )

target_link_libraries(main ${OpenCV_LIBS})

# Tell cmake than when "make clean" also nuke everything in output folder
set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES "${CMAKE_SOURCE_DIR}/output"
)