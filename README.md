![CI status](https://github.com/ParaCoToUl/noarr/workflows/Noarr%20test%20ubuntu-latest%20-%20clang/badge.svg)
![CI status](https://github.com/ParaCoToUl/noarr/workflows/Noarr%20test%20ubuntu-latest%20-%20gcc/badge.svg)

![CI status](https://github.com/ParaCoToUl/noarr/workflows/Noarr%20test%20macosl/badge.svg)

![CI status](https://github.com/ParaCoToUl/noarr/workflows/Noarr%20test%20Win/badge.svg)

# Noarr Structures

Library that helps programmer with data serialization independently on underlying design.


## Using the library

Noarr structures is a header-only library, so only include path need to be added. The include path should point to the `/include` folder of this repository.

```cmake
# the CMake line that adds the include directory
target_include_directories(<my-app> PUBLIC <cloned-repo-path>/include)
```

The library requires C++ 17.


## Running tests and examples

Enter the desired folder (`examples/matrix`). In the terminal (linux bash, windows cygwin or gitbash) run the following commands:

```sh
# generates build files for your platform
cmake .

# builds the project using previously generated build files
cmake --build .

# run the built executable
# (this step differs by platform, this example is for linux)
./matrix || ./test-runner
```
