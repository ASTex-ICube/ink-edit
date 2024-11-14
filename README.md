#CCVT


## Compilation
You need some classic development tools
- git
- cmake 3.0 min
- a _recent_ C++ compiler
    - g++
    - clang
    - Visual Studio C++

### Dependencies
* CGAL
* glfw3
* GLEW 
* metis 
* BLAS
* LAPACK
* TBB 
* suitesparse 

# Installation


## Linux
Just install packages:
- lib-cgal-dev
- libglew-dev
- libglfw3-dev
- libtbb-dev
- libsuitesparse-dev
- liblapack-dev
- liblas-dev
- libmetis-dev

## Mac OS/X
The most simple way to install dependencies is to use [homebrew](https://brew.sh/) package system.
Then you can install the dependencies:
- brew install cgal glew glfw3 tbb suitesparse lapack blas metis

## Windows
The most simple way to install dependencies is to use [vcpkg](https://vcpkg./) package system.
Then you can install the dependencies:
vcpkg.exe install cgal glew glfw3 tbb suitesparse lapack blas metis

### install VCPKG
- open a power-shell
- get wcpkg (Donwload zip or git clone https://github.com/Microsoft/vcpkg.git )
- cd  vcpkg
- .\bootstrap-vcpkg.bat

### install dependencies
- .\vcpkg.exe install png openexr glfw3 assimp eigen3

### Compilation
- launch CMake, chose src dir and binary dir
- Configure
- Choose Specify tool chain file and set file: `XXXX/vcpkg/scripts/buildsystems/vcpkg.cmake`
- Generate
- Launch Solution
- compile (select Release configuration) and run

