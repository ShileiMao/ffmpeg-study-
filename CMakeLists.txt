cmake_minimum_required(VERSION 3.14)
project(player C CXX)
# c++ 14 standard
set(CMAKE_CXX_STANDARD 14)

# add glfw folder into the build
add_subdirectory(lib/glfw)
# add ffmpeg into the build
add_subdirectory(lib/ffmpeg)

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
    "-lGL -lGLU -lX11"
  )
endif()

list(APPEND SOURCES
  src/main.cpp
  src/load_frame.cpp
)
add_executable(player ${SOURCES})

# link the glfw library 
target_link_libraries(player FFmpeg glfw ${EXTRA_LIBS})