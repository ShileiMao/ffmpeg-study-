prepare to build:
1. install home brew 
2. brew install cmake
3. brew install ffmpeg 
4. brew install pkg-config # this used to search the ffmpeg libraries in the CMakeLists

To generate the xcode project:
  ```
  mkdir build && cd build
  cmake .. -G Xcode
  ```

