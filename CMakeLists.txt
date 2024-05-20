#
# Shizu
# Copyright (C) 2023-2024 Michael Heilmann. All rights reserved.
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

cmake_minimum_required(VERSION 3.20)

# Set the project name.
project(Shizu LANGUAGES C)
set(Shizu.project-name "Shizu")

# To simply things.
set(name "Shizu")

include(FetchContent)

#######################################################################################################################

set(idlib-process.repository CACHE STRING "IdLib Process: The Git repository to check out")
if (NOT idlib-process.repository)
  set(idlib-process.repository https://github.com/michaelheilmann/idlib-process.git)
endif()

set(idlib-process.tag CACHE STRING "IdLib Process: The Git tag to check out")
if (NOT idlib-process.tag)
  set(idlib-process.tag 1.4)
endif()

set(idlib-process.source-dir CACHE STRING "IdLib Process: Path to the source directory")
if (NOT idlib-process.source-dir)
  set(idlib-process.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-src")
endif()

set(idlib-process.binary-dir CACHE STRING "IdLib Process: Path to the build directory")
if (NOT idlib-process.binary-dir)
  set(idlib-process.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-process-1.4-bld")
endif()

#######################################################################################################################

set(idlib-bit-scan.repository CACHE STRING "IdLib Bit Scan: The Git repository to check out")
if (NOT idlib-bit-scan.repository)
  set(idlib-bit-scan.repository https://github.com/michaelheilmann/idlib-bit-scan.git)
endif()

set(idlib-bit-scan.tag CACHE STRING "IdLib Bit Scan: The Git tag to check out")
if (NOT idlib-bit-scan.tag)
  set(idlib-bit-scan.tag 1.4)
endif()

set(idlib-bit-scan.source-dir CACHE STRING "IdLib Bit Scan: Path to the source directory")
if (NOT idlib-bit-scan.source-dir)
  set(idlib-bit-scan.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-bit-scan-1.4-src")
endif()

set(idlib-bit-scan.binary-dir CACHE STRING "IdLib Bit Scan: Path to the build directory")
if (NOT idlib-bit-scan.binary-dir)
  set(idlib-bit-scan.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-bit-scan-1.4-bld")
endif()

#######################################################################################################################

set(idlib-file-system.repository CACHE STRING "IdLib File System: The Git repository to check out")
if (NOT idlib-file-system.repository)
  set(idlib-file-system.repository https://github.com/michaelheilmann/idlib-file-system.git)
endif()

set(idlib-file-system.tag CACHE STRING "IdLib File System: The Git tag to check out")
if (NOT idlib-file-system.tag)
  set(idlib-file-system.tag 1.7)
endif()

set(idlib-file-system.source-dir CACHE STRING "IdLib File System: Path to the source directory")
if (NOT idlib-file-system.source-dir)
  set(idlib-file-system.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-file-system-1.7-src")
endif()

set(idlib-file-system.binary-dir CACHE STRING "IdLib File System: Path to the build directory")
if (NOT idlib-file-system.binary-dir)
  set(idlib-file-system.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-file-system-1.7-bld")
endif()

#######################################################################################################################

set(idlib-array.repository CACHE STRING "IdLib Array: The Git repository to check out")
if (NOT idlib-array.repository)
  set(idlib-array.repository https://github.com/michaelheilmann/idlib-array.git)
endif()

set(idlib-array.tag CACHE STRING "IdLib Array: The Git tag to check out")
if (NOT idlib-array.tag)
  set(idlib-array.tag 1.0)
endif()

set(idlib-array.source-dir CACHE STRING "IdLib Array: Path to the source directory")
if (NOT idlib-array.source-dir)
  set(idlib-array.source-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-array-1.0-src")
endif()

set(idlib-array.binary-dir CACHE STRING "IdLib Array: Path to the build directory")
if (NOT idlib-array.binary-dir)
  set(idlib-array.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/idlib-array-1.0-bld")
endif()

FetchContent_Declare(idlib-array
                     GIT_REPOSITORY ${idlib-array.repository}
                     GIT_TAG ${idlib-array.tag}
                     SOURCE_DIR ${idlib-array.source-dir}
                     BINARY_DIR ${idlib-array.binary-dir})

#######################################################################################################################

set(Shizu.Runtime.repository CACHE STRING "Shizu Runtime: The Git repository to check out")
if (NOT Shizu.Runtime.repository)
  set(Shizu.Runtime.repository https://github.com/michaelheilmann/shizu-runtime.git)
endif()

set(Shizu.Runtime.tag CACHE STRING "Shizu Runtime: The Git tag to check out")
if (NOT Shizu.Runtime.tag)
  set(Shizu.Runtime.tag "develop")
endif()

set(Shizu.Runtime.source-dir CACHE STRING "Shizu.Runtime: Path to the source directory")
if (NOT Shizu.Runtime.source-dir)
  set(Shizu.Runtime.source-dir "${CMAKE_CURRENT_BINARY_DIR}/shizu-runtime-develop-src")
endif()

set(Shizu.Runtime.binary-dir CACHE STRING "Shizu.Runtime: Path to the binary directory")
if (NOT Shizu.Runtime.binary-dir)
  set(Shizu.Runtime.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/shizu-runtime-develop-bld")
endif()

FetchContent_Declare(Shizu.Runtime
                     GIT_REPOSITORY ${Shizu.Runtime.repository}
                     GIT_TAG ${Shizu.Runtime.tag}
                     SOURCE_DIR ${Shizu.Runtime.source-dir}
                     BINARY_DIR ${Shizu.Runtime.binary-dir})

#######################################################################################################################

FetchContent_MakeAvailable(Shizu.Runtime idlib-array)

#######################################################################################################################

# Enable testing.
enable_testing()

# Add subdirectories.
add_subdirectory(libraries)
add_subdirectory(clients)
add_subdirectory(servers)
