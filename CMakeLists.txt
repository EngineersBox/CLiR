cmake_minimum_required(VERSION 3.10)

project(CLiR VERSION 1.0)

# Debug
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g -O1")

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CXXFLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include source content
file (GLOB_RECURSE CLiR_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE CLiR_HEADERS CONFIGURE_DEPENDS "src/*.hpp")

set (CLiR_INCLUDE_DIRS "")
foreach (_headerFile ${CLiR_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND CLiR_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES CLiR_INCLUDE_DIRS)

# Mark executable
add_executable(CLiR ${CLiR_SOURCES})
target_include_directories(CLiR PRIVATE ${CLiR_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(CLiR PUBLIC ${OPENGL_INCLUDE_DIR})
target_include_directories(CLiR PUBLIC ${OPENGL_LIBRARIES})
target_link_libraries(CLiR PUBLIC ${OPENGL_LIBRARIES})

# OpenCL
find_package(OpenCL REQUIRED)
target_link_libraries(CLiR PRIVATE ${OpenCL_LIBRARIES})
target_include_directories(CLiR PRIVATE ${OpenCL_INCLUDE_DIRS})

# GLFW 3
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(CLiR PRIVATE glfw)

# GLEW
find_package(GLEW REQUIRED)
target_link_libraries(CLiR PRIVATE GLEW::GLEW)

# GLM
find_package(glm CONFIG REQUIRED)
target_link_libraries(CLiR PRIVATE glm::glm)

# spdlog
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(CLiR PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

# boost
find_package(Boost REQUIRED COMPONENTS filesystem iostreams)
if (NOT TARGET Boost::filesystem)
    add_library(Boost::filesystem IMPORTED INTERFACE)
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::filesystem PROPERTY
            INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
if (NOT TARGET Boost::iostreams)
    add_library(Boost::iostreams IMPORTED INTERFACE)
    set_property(TARGET Boost::iostreams PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    set_property(TARGET Boost::iostreams PROPERTY
            INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()
target_link_libraries(CLiR PRIVATE Boost::filesystem Boost::iostreams)

