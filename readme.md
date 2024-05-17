prepare to build:
1. install homebrew 
2. brew install cmake
3. brew install ffmpeg 
4. brew install pkg-config # this used to search the ffmpeg libraries in the CMakeLists

  ``` shell
  brew install cmake ffmpeg pkg-config
  ```

To clone the repository (with the sub repository):
  ``` shell 
  git clone [url] --recursive
  ```

Or:
  ```
  git checkout [url]
  git submodule update --recursive --remote
  ```


To generate the xcode project:
  ``` shell
  mkdir build && cd build
  cmake .. -G Xcode
  ```

