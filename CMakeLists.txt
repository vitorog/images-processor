project(ImageEffects)
cmake_minimum_required(VERSION 3.0)
find_package( OpenCV REQUIRED )
find_package( OpenGL REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#set(CMAKE_PREFIX_PATH "D:/Programs/Windows/Qt/Qt5.4.0/lib/cmake/Qt5Widgets")
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})

find_package(Qt5Core REQUIRED)
include_directories(${Qt5Core_INCLUDES})
add_definitions(${Qt5Core_DEFINITIONS})

find_package(Qt5OpenGL REQUIRED)
include_directories(${Qt5OpenGL_INCLUDES})
add_definitions(${Qt5OpenGL_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")

set(GLEW_INCLUDE_DIR "E:/Development/Libs/glew-1.10.0_mingw/include")
find_package( GLEW REQUIRED )

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB FORMS "*.ui")

set(GLM_PATH "E:/Development/Libs/glm-0.9.5.2/glm")

include_directories("../shade-framework")
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLM_PATH})


qt5_wrap_ui(UI_MOC "main_window.ui")

set(SHADE_FRAMEWORK_LIBS "E:/Development/Repositories/Builds/shade-framework-build/libshade-framework.dll")


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${UI_MOC})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES}
${Qt5OpenGL_LIBRARIES} ${OpenCV_LIBS} ${SHADE_FRAMEWORK_LIBS})
