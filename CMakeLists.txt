# This file was copy-pasted from https://github.com/libigl/libigl/blob/master/tutorial/CMakeLists.txt
# and edited for our needs
cmake_minimum_required(VERSION 2.8.12)
project(nanomeshviewer)

### libIGL options: choose between header only and compiled static library
option(LIBIGL_USE_STATIC_LIBRARY "Use LibIGL as static library" ON)
option(LIBIGL_WITH_VIEWER      "Use OpenGL viewer"  ON)
option(LIBIGL_WITH_NANOGUI     "Use Nanogui menu"   OFF)

### libIGL options: choose your dependencies (by default everything is OFF, in this example we need the viewer) ###
option(LIBIGL_WITH_EMBREE           "Use Embree"         ON)
option(LIBIGL_WITH_LIM              "Use LIM"            ON)
option(LIBIGL_WITH_OPENGL           "Use OpenGL"         ON)
option(LIBIGL_WITH_OPENGL_GLFW      "Use OpenGL GLFW"    ON)
option(LIBIGL_WITH_PNG              "Use PNG"            ON)
option(LIBIGL_WITH_XML              "Use XML"            ON)
option(LIBIGL_WITH_DRACO            "Use Draco"          ON)
### End   to be tested ----

### Adding libIGL: choose the path to your local copy libIGL ###
### This is going to compile everything you requested ###
add_subdirectory("${LIBIGL_DIR}/shared/cmake" "libigl")

### Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

### Compilation flags: adapt to your needs ###
if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj") ### Enable parallel compilation
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR} )
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR} )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w") # disable all warnings (not ideal but...)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") #### Libigl requires a modern C++ compiler that supports c++11
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../" )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") # disable all warnings (not ideal but...)
endif()

# Enable openMP if possible
#find_package(OpenMP)
#if (OPENMP_FOUND AND NOT WIN32)
#  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif()

### Prepare the build environment
include_directories(${LIBIGL_INCLUDE_DIRS})
add_definitions(${LIBIGL_DEFINITIONS})

### Nanomeshviewer specific section
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}_bin main.cpp)
target_include_directories(${PROJECT_NAME}_bin PRIVATE ${LIBIGL_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME}_bin PRIVATE ${LIBIGL_DEFINITIONS})
target_link_libraries(${PROJECT_NAME}_bin ${LIBIGL_LIBRARIES} ${LIBIGL_VIEWER_EXTRA_LIBRARIES} ${LIBIGL_OPENGL_EXTRA_LIBRARIES} ${LIBIGL_OPENGL_GLFW_EXTRA_LIBRARIES} ${LIBIGL_DRACO_EXTRA_LIBRARIES})