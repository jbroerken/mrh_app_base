# mrh_app_base

<p align="center">
<img width="100%" height="100%" src="/doc/source/banner.png">
</p>


## About

The mrh_app_base project serves as a starting point for application development.
This project provides a basic structure to build on, structuring everything based aroung a CMake build.

This projects includes both the template for a executable MRH application as well as a MRH application service.
The default setting is to both compile a application and application service.

The code as well as the documentation includes information about the actual functions and what they do.
Please refer to the library documentations for more information about how modules, application files and more work.


## Requirements

#### Compilation

This project is built using CMake. You can find CMake here:

https://cmake.org/

#### Library Dependencies

This project requires other libraries and headers to function:

Dependency | Source
---------- | ------
libmrh |  https://github.com/jbroerken/libmrh/
libmrhab | https://github.com/jbroerken/libmrhab/
libmrhbf |  https://github.com/jbroerken/libmrhbf/
libmrhevdata | https://github.com/jbroerken/libmrhevdata/
libmrhs | https://github.com/jbroerken/libmrhs/
libmrhvt | https://github.com/jbroerken/libmrhvt/
mrhshared | https://github.com/jbroerken/mrhshared/

For more information about the requirements, check the "Building" section found in the documentation.


## Documentation

All documentation is build with sphinx-doc using the Read The Docs theme.
To build the documentation, grab the requirements for it:

#### sphinx-doc
https://www.sphinx-doc.org/en/master/

#### Read The Docs Theme
https://sphinx-rtd-theme.readthedocs.io/en/stable/

## Licence

This project is licenced under the ZLib licence. 
Please read the included LICENCE.txt for the exact terms.


## Directories

This project supplies multiple directories for the development of said project. 
Their names and descriptions are as follows:

Directory | Description
--------- | -----------
bin | Contains the built project executables.
build | CMake build directory.
doc | Documentation files.
include | Static library header files used by the project.
lib | Static library files used by the project.
pkg | The project package directory (files, configuration, etc.).
src | Project source code.
