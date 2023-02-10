cmake_minimum_required(VERSION 3.21)
set(PROJECT_TARGET CLiR)
project(${PROJECT_TARGET} C)

set(CMAKE_C_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

# ---- BUILDS ---- #

# Build Types
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE}
        CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel tsan asan lsan msan ubsan"
        FORCE)

# Release
set(CMAKE_C_FLAGS_RELEASE
        "-O3 -pthread -lm"
        CACHE STRING "Flags used by the C compile during release builds."
        FORCE)

# Debug
set(CMAKE_C_FLAGS_DEBUG
        "-O0 -Wall -pthread -lm -g -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C compile during release builds."
        FORCE)

# ThreadSanitizer
set(CMAKE_C_FLAGS_TSAN
        "-fsanitize=thread -Wall -g -pthread -lm -O1 -g -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C compiler during ThreadSanitizer builds."
        FORCE)

# AddressSanitize
set(CMAKE_C_FLAGS_ASAN
        "-fsanitize=address -Wall -fno-optimize-sibling-calls -fsanitize-address-use-after-scope -fno-omit-frame-pointer -g -O1 -pthread -lm"
        CACHE STRING "Flags used by the C compiler during AddressSanitizer builds."
        FORCE)

# LeakSanitizer
set(CMAKE_C_FLAGS_LSAN
        "-fsanitize=leak -Wall -fno-omit-frame-pointer -g -O1 -pthread -lm"
        CACHE STRING "Flags used by the C compiler during LeakSanitizer builds."
        FORCE)

# MemorySanitizer
set(CMAKE_C_FLAGS_MSAN
        "-fsanitize=memory -Wall -fno-optimize-sibling-calls -fsanitize-memory-track-origins=2 -fno-omit-frame-pointer -g -O2 -pthread -lm"
        CACHE STRING "Flags used by the C compiler during MemorySanitizer builds."
        FORCE)

# UndefinedBehaviour
set(CMAKE_C_FLAGS_UBSAN
        "-O3 -fsanitize=undefined -Wall -pthread -lm -g -fno-omit-frame-pointer"
        CACHE STRING "Flags used by the C compiler during UndefinedBehaviourSanitizer builds."
        FORCE)

message("[${PROJECT_TARGET}] Configured build type: ${CMAKE_BUILD_TYPE}")
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

