cmake_minimum_required(VERSION 3.23 FATAL_ERROR)
set (CMAKE_CXX_STANDARD 17)
project(minecraft)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Add .lib files
link_directories(${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# OpenGL
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
if(UNIX)
find_package(X11 REQUIRED)
endif(UNIX)

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

#set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype ${ASSIMP_LIBRARY})
if(UNIX)
set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
endif(UNIX)
if(WIN32)
set(LIBS ${GLFW3_LIBRARY})
endif(WIN32)
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

# Put all libraries into a variable
#set(LIBS glfw3 opengl32 GLAD)
#set(LIBS glfw3 GL)

# GLAD
add_library(GLAD "vendor/glad.c")
set(LIBS ${LIBS} GLAD)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
	"${CMAKE_SOURCE_DIR}/vendor"
)

# Add source files
# CMAKE_SOURCE_DIR refers to directory containing CMakeLists.txt
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)


add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
if(WIN32)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/res)
file(COPY res/cube.png DESTINATION ${CMAKE_BINARY_DIR}/res/)
file(COPY res/grass1.png DESTINATION ${CMAKE_BINARY_DIR}/res/)
file(COPY res/grass2.png DESTINATION ${CMAKE_BINARY_DIR}/res/)
file(COPY ${CMAKE_SOURCE_DIR}/src/cube_shader.frag DESTINATION ${CMAKE_BINARY_DIR}/res/)
file(COPY ${CMAKE_SOURCE_DIR}/src/cube_shader.vert DESTINATION ${CMAKE_BINARY_DIR}/res/)
endif(WIN32)

# Define the link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})
