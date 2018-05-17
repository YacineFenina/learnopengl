cmake_minimum_required(VERSION 3.0.0)

set(PROJ_NAME Triangle)

project(${PROJ_NAME})

find_package(OpenGL REQUIRED)
link_libraries(${OPENGL_LIBRARY})
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(glfw3 3.2 REQUIRED)
set(GLFW_INCLUDE_PATH "" CACHE PATH "The directory that contains GL/glfw.h" )

find_library(DLFCN_LIBRARY dl)


find_package(glm REQUIRED)
# Define GLM_INCLUDE_DIRS
if (GLM_FOUND)
  include_directories(${GLM_INCLUDE_DIR})
  link_libraries(${GLM_LIBRARY})
  message(${GLM_LIBRARY})
endif()


file(
    GLOB_RECURSE
    source_files
    src/*
)

file(
    GLOB_RECURSE
    header_files
    header/*
)

include_directories(
	${GLFW_INCLUDE_PATH}
)

add_executable(
    ${PROJ_NAME}
    ${source_files}
    ${header_files}
    
)

message("on cherche opengl ${OPENGL_LIBRARY}")
message("on cherche glew ${GLEW_LIBRARIES}")

target_link_libraries(
    ${PROJ_NAME}
    ${DLFCN_LIBRARY}
    glfw
)
