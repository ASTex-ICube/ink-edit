# Ink-Edit: Interactive color-constrained textures editing

## Interactive interface implementation for the article Ink-Edit

Interactive color-constrained textures editing, proceeding SIGGRAPH Asia
2024 Technical Communications (SA Technical Communications ’24),
December 3–6, 2024, Tokyo, Japan.
https://doi.org/10.1145/3681758.3697991


## citation 
- article
@article{GMS24,
     title={Ink-Edit: Interactive color-constrained textures editing},
     author={Grenier, Charline and Memari, Pooran and Sauvage, Basile},
     journal={ACM Transactions on Graphics (TOG)},
     year={2024},
     publisher={ACM New York, NY, USA},
     doi={10.1145/3681758.3697991}
}

- code
@software {InkEditCode,
     title = {Ink-Edit: Interactive color-constrained textures editing -
code},
     author = {Grenier, Charline and Memari, Pooran and Sauvage, Basile},
     date = {2024},
     url = {https://github.com/ASTex-ICube/ink-edit}
}


## Compilation
You need some classic development tools
- git
- cmake 3.0 min
- a _recent_ C++ compiler
    - g++
    - clang
    - Visual Studio C++

and some dépendencies (external libraries)
* CGAL
* glfw3
* GLEW 
* metis 
* BLAS
* LAPACK
* TBB 
* suitesparse 

### Linux
Just install packages: for example on Debian/Ubuntu
` apt install libcgal-dev libglew-dev libglfw3-dev libtbb-dev libsuitesparse-dev liblapack-dev libblas-dev libmetis-dev `

## Mac OS/X
The most simple way to install dependencies is to use [homebrew](https://brew.sh/) package system.
Then you can install the dependencies:
- brew install cgal glew glfw3 tbb suitesparse lapack blas metis

### Windows
The most simple way to install dependencies is to use [vcpkg](https://vcpkg./) package system.

#### install VCPKG
- get wcpkg (Donwload zip or git clone https://github.com/Microsoft/vcpkg.git )
- open a powershell and go inside the directory:
- `cd  vcpkg`
- `.\bootstrap-vcpkg.bat`|

#### install dependencies
- .\vcpkg.exe install cgal glew glfw3 tbb suitesparse lapack blas metis

### Compilation
- launch CMake, chose src dir and binary dir
- Configure
- Choose Specify tool chain file for cross compiling and set file: `XXXX/vcpkg/scripts/buildsystems/vcpkg.cmake`
- Generate
- Launch Solution
- compile (select Release configuration) and run

