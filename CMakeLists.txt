# This file is part of MRVN-Explorer under the MIT license
# Source code & license avalible at https://github.com/MRVN-Radiant/MRVN-Explorer
cmake_minimum_required( VERSION 3.12 )

project( explorer )


set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build )

if(WIN32)
    add_compile_definitions(WIN32)
endif()

# Executable
add_executable( explorer )

target_sources( explorer
                PRIVATE
                    explorer/main.cpp
                    explorer/ui/cmainwindow.cpp
                    explorer/utils/logging.cpp
                    explorer/core/cscene.cpp
                    explorer/core/bsp/ibsp.cpp
                    explorer/core/bsp/apex_legends/apexlegends.cpp
                    explorer/core/bsp/apex_legends/apexlegends_render.cpp
                    explorer/core/bsp/apex_legends/apexlegends_windows.cpp
                    explorer/core/bsp/titanfall/titanfall.cpp
                    explorer/core/bsp/titanfall/titanfall_render.cpp
                    explorer/core/bsp/titanfall/titanfall_windows.cpp
                    explorer/renderer/crenderer.cpp
                    explorer/renderer/ccamera.cpp
)

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui)


target_sources( explorer
                PRIVATE
                    ${IMGUI_DIR}/imgui_demo.cpp
                    ${IMGUI_DIR}/imgui_draw.cpp
                    ${IMGUI_DIR}/imgui_tables.cpp
                    ${IMGUI_DIR}/imgui_widgets.cpp
                    ${IMGUI_DIR}/imgui.cpp

                PRIVATE
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)

target_include_directories( explorer
                            PUBLIC ${IMGUI_DIR}
                            PUBLIC ${IMGUI_DIR}/backends
)

if(WIN32)
    target_link_libraries( explorer
                           -static -lpthread
                         )
endif()


# GLFW
find_package( glfw3 3.3 REQUIRED )
target_link_libraries( explorer glfw )

# OpenGL
find_package( OpenGL REQUIRED )
target_link_libraries( explorer ${OPENGL_LIBRARIES} )


#include(FindGLEW)
find_package( GLEW REQUIRED )
target_link_libraries( explorer ${GLEW_LIBRARIES} )
add_library(GLEW STATIC IMPORTED ${GLEW_LIBRARIES})

# Spdlog
find_package( spdlog REQUIRED )
target_link_libraries( explorer spdlog::spdlog_header_only)

# Copy shaders to build dir
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic.frag DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders/basic.vert DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
