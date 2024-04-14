#
# Shizu
# Copyright (C) 2018-2024 Michael Heilmann. All rights reserved.
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

# Macro to define an enumeration of C compilers and detect what C compiler is used.
#
# First, the enumeration constants ${target}_compiler_c_(unknown|clang|msvc|gcc) are defined.
# Each constant is a string of an unique name identifying a C compiler.
#
# Second, the constant ${target}.compiler_c is set to the {target}.compiler_c_* values denoting the detected C compiler.
#
# @param target The target.
macro(detect_c_compiler target)
  # An unknown compiler.
  set(${target}.compiler_c_unknown "<unknown compiler>")

  # CLANG.
  set(${target}.compiler_c_clang "CLANG")

  # MSVC.
  set(${target}.compiler_c_msvc "MSVC")

  # GCC.
  set(${target}.compiler_c_gcc "GCC")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}.compiler_c)
    set(${target}.compiler_c ${${target}.compiler_c_unknown})
  endif()
  # Perform detection.
  if (CMAKE_C_COMPILER_ID)
    if (CMAKE_C_COMPILER_ID MATCHES ".*clang")
      set(${target}.compiler_c ${${target}.compiler_c_clang})
    endif()
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set(${target}.compiler_c ${${target}.compiler_c_gcc})
    endif()
    if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
      set(${target}.compiler_c ${${target}.compiler_c_msvc})
    endif()
  endif()
  message( STATUS " - ${target} C compiler: ${${target}.compiler_c}")
endmacro()

# Macro to define an enumeration of C++ compilers and detect what C++ compiler is used.
#
# First, the enumeration constants ${target}_compiler_cpp_(unknown|clang|msvc|gcc) are defined.
# Each constant is a string of an unique name identifying a C++ compiler.
#
# Second, the constant ${target}.compiler_cpp is set to the {target}.compiler_cpp_* values denoting the detected C++ compiler.
#
# @param target The target.
macro(detect_cpp_compiler target)
  # An unknown compiler.
  set(${target}.compiler_cpp_unknown "<unknown>")

  # CLANG.
  set(${target}.compiler_cpp_clang "CLANG")

  # MSVC.
  set(${target}.compiler_cpp_msvc "MSVC")

  # GCC.
  set(${target}.compiler_cpp_gcc "GCC")

  # Initialize if not yet initialized.
  if (NOT DEFINED ${target}.compiler_cpp)
    set(${target}.compiler_cpp ${${target}.compiler_cpp_unknown})
  endif()
  if (CMAKE_CXX_COMPILER_ID)
    if (CMAKE_CXX_COMPILER_ID MATCHES ".*clang")
      set(${target}.compiler_cpp ${${target}.compiler_cpp_clang})
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(${target}.compiler_cpp ${${target}.compiler_cpp_gcc})
    endif()
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
      set(${target}.compiler_cpp ${${target}.compiler_cpp_msvc})
    endif()
  endif()
  message( STATUS " - ${target} C++ compiler: ${${target}.compiler_cpp}")

endmacro()
