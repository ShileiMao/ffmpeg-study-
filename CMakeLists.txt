cmake_minimum_required(VERSION 3.14)
project(player C CXX)
# c++ 14 standard
set(CMAKE_CXX_STANDARD 14)

# add ffmpeg into the build
add_subdirectory(lib/ffmpeg)

add_subdirectory(lib/glad)
# add glfw folder into the build
# add_subdirectory(lib/glfw)

# add_definitions(-DGL_SILENCE_DEPRECATION)

if(APPLE) 
  list(APPEND EXTRA_LIBS 
    "-framework OpenGL"
  )
elseif(WIN32)
  list(APPEND EXTRA_LIBS
    "-lglu32 -lopengl32"
  )
  set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
else() # linux
  list(APPEND EXTRA_LIBS 
    "-lGL -lX11"
    # "-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl"
  )
endif()

list(APPEND SOURCES
  src/main.cpp
  src/video_reader.hpp
  src/video_reader.cpp
  src/render_color.hpp
  src/render_color.cpp
  src/load_frame.hpp
  src/load_frame.cpp
  src/gui/Window.hpp 
  src/gui/Window.cpp
  src/gui/gl/Shader.hpp
  src/gui/gl/Shader.cpp
  src/utils/stb_image.h
)
add_executable(player ${SOURCES})

# link the glfw library 
target_link_libraries(player FFmpeg glfw glad ${EXTRA_LIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tests/resources/gl/shaders/fragment.fs
  ${CMAKE_CURRENT_BINARY_DIR}/resources/gl/shaders/fragment.fs COPYONLY
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tests/resources/gl/shaders/vertex.vs
  ${CMAKE_CURRENT_BINARY_DIR}/resources/gl/shaders/vertex.vs COPYONLY
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tests/cat_image.jpg
  ${CMAKE_CURRENT_BINARY_DIR}/resources/images/cat_image.jpg COPYONLY
)