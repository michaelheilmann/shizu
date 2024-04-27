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

# Remember the path to the cmake directory.
set(Shizu.cmake-files-dir ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# To simply things.
set(name "Shizu")

include(FetchContent)

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
  set(Shizu.Runtime.source-dir "${CMAKE_CURRENT_BINARY_DIR}/shizu-runtime-develop")
endif()

set(Shizu.Runtime.binary-dir CACHE STRING "Shizu.Runtime: Path to the binary directory")
if (NOT Shizu.Runtime.binary-dir)
  set(Shizu.Runtime.binary-dir "${CMAKE_CURRENT_BINARY_DIR}/shizu-runtime-develop")
endif()

FetchContent_Declare(Shizu.Runtime
                     GIT_REPOSITORY ${Shizu.Runtime.repository}
                     GIT_TAG ${Shizu.Runtime.tag}
                     SOURCE_DIR ${Shizu.Runtime.source-dir}
                     BINARY_DIR ${Shizu.Runtime.binary-dir})

#######################################################################################################################

FetchContent_MakeAvailable(Shizu.Runtime)

#######################################################################################################################

# Include the cmake library.
include(${Shizu.cmake-files-dir}/all.cmake)

# Enable testing.
enable_testing()

# Add subdirectories.
add_subdirectory(clients)
add_subdirectory(servers)
