Learning OpenCV
======
## How to build OpenCV from source code
* [Using Visual Studio and CMake](https://www.youtube.com/watch?v=_fqpYLM6SCw&list=PLBAic7KjrRUBHXhnbvtjN2m5fghNgyDRW&index=1)

## How to build demo OpenCV using Visual Studio
* [OpenCV 4 Building with CMake & Visual Studio 2017 Setup](https://www.youtube.com/watch?v=By-PKbWDZNk&list=PLBAic7KjrRUBHXhnbvtjN2m5fghNgyDRW&index=2)

## How to build demo OpenCV using VS Code
* Install VS Code plugins:
  * CMake (twxs)
  * CMake Tools (Microsoft)
* From VS Code menu
  * View > Command Palette ...
    * <span style="color:green">CMake: Quick Start</span> : to generate **CMakeLists.txt**
    * <span style="color:green">CMake: Configure</span> : to generate **build folder**
    * <span style="color:green">CMake: Build</span> : to generate **.exe file**
    * Edit **CMakeLists.txt** as my git hub
      * find_package(OpenCV REQUIRED)
      * target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
    * <span style="color:green">C/C++ Edit Configurations (JSON)</span> : to add OpenCV include header path in **includePath** section
* <span style="color:red">Note :</span> You MUST change CMake build target appropriate with OpenCV build target from **VS code footer bar** when recived warning: *"Found OpenCV Windows Pack but it has no binaries compatible with your configuration.
You should manually point CMake variable OpenCV_DIR to your build of OpenCV library."*
## Ebooks
* [All IT ebooks](http://www.allitebooks.org/?s=opencv)