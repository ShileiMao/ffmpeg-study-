### checkout the source code 
 
 To clone the repository (with the sub repository):
  ``` shell 
  git clone [url] --recursive
  ```

 Or:
  ```
  git checkout [url]
  git submodule update --init --recursive # only run first time
  git submodule update --recursive --remote
  ```

### prepare to build (Mac Os):
1. install homebrew 
2. brew install cmake
3. brew install ffmpeg 
4. brew install pkg-config # this used to search the ffmpeg libraries in the CMakeLists
  ``` shell
  brew install cmake ffmpeg pkg-config
  ```



### Build on Linux (Ubuntu):
1. In order to build glfw:
 refer to [here](https://www.glfw.org/docs/3.3/compile.html#:~:text=GLFW%20uses%20CMake%20to%20generate,to%20compile%20the%20GLFW%20library.)

 `sudo apt install xorg-dev`
<!-- 2. `sudo dnf install libXcursor-devel libXi-devel libXinerama-devel libXrandr-devel` -->

2. In order to build ffmpeg:  
  ``` shell
  apt-get install ffmpeg libav-tools libavcodec-dev libavcodec57 libavdevice-dev libavdevice57 libavfilter-dev libavfilter6 libavformat-dev libavformat57 libavresample-dev libavresample3 libavutil-dev libavutil55 libpostproc-dev libpostproc54 libswresample-dev libswresample2 libswscale-dev libswscale4
  ```


### general build process
1. To build:
  ``` shell
  mkdir build
  cd build
  cmake ..
  make  
  ```


2. To generate the xcode project:
  ``` shell
  mkdir build && cd build
  cmake .. -G Xcode
  ```

