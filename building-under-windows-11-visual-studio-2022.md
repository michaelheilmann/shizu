# Building under Windows 11/Visual Studio Community 2022

## Installing the dependencies

*Shizu* requires
- *Microsoft Visual Studio Community 2022* Version 17.9.2 or better.
  *Microsoft Visual Studio Community 2022* is available at [https://visualstudio.microsoft.com/vs/community/](https://visualstudio.microsoft.com/vs/community/).
- *Kitware CMake* Version 3.28.3 or better.
  *Kitware CMake* is available at [https://cmake.org/](https://cmake.org/).

## Building the program
The following instructions will perform an out-of-source build. An out-of-source build does not modify the source directory
by storing any build file, intermediate file, or product file in a dedicated build directory outside of the source directory.
An out of source build is the recommended way of building *Shizu*.

- Checkout `Shizu` [https://github.com/michaelheilmann/shizu.git](https://github.com/michaelheilmann/shizu.git) into a directory in your file system.
  For the remainder of this manual, we call this directory *source directory* and denote it in command-line prompts by the meta variable `<source-directory>`.
- Create a directory outside of the *source directory* in which the build will be performed.
  That directory *must not* reside in the source directory `<source-directory>`.
  For the remainder of this manual, we call this directory *build directory* and denote it in command-line prompts by the meta variable `<build-directory>`.
- Open a console and enter the build directory `<build-directory>`.
- Enter `cmake <source-directory>`.
- The Visual Studio Community 2022 solution file `Shizu.sln` should have been generated in `<build-directory>`.
