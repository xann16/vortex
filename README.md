# vortex
Experimental C++ framework for parallelizable numerical solvers focusing on computational fluid dynamics with C and Fortran bindings.


## Quick Setup and Usage

Basic setup (to be improved and more detailed):

- currently tested on Linux (Ubuntu) and partially for MacOS (both Intel x64 - v13, and arm64 - v14); Windows not yet checked
- requires installed compiler that supports C++20 - curently tested for g++ (versions: 11, 12, 13) and clang++ (versions: 18, 19)
- other required tools (newer, the better; see `.github/workflows/ci.yml` for more details which versions are used for testing): CMake, Ninja (build system), Conan2 (package manager)
- also requires valid installation of MPI - either OpenMPI or MPICH (both Linux and MacOS), or IntelMPI (for Linux only)

Given above requirements are met, following commands may be used to build and test `vortex`:

```shell
# setup dependencies via Conan
conan profile detect
conan install conanfile.txt --build=missing

# configure and build via CMake
cmake -S . -B ./build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build ./build -v

# run tests via CTest
cd build
ctest --output-on-failure
```

### Tools

#### Vortex Settings Wizard (`vxsw`)

- Python tool located in `tools/settings-wizard/src`
- assumes installed Anaconda
- setup env:

```shell
conda create -n vxsw python=3.12
```

- run script `vxsw.py` to regenerate settings code boilerplate (TODO)



      - name: Setup Dependencies via Conan
        run: |
          conan profile detect
          conan install conanfile.txt --build=missing

      - name: Configure CMake Project
        run: |
          cmake -S . -B ./build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON

      - name: Build Project
        run: |
          cmake --build ./build -v

      - name: Run Tests
        working-directory: ./build
        run: |
          ctest --output-on-failure
