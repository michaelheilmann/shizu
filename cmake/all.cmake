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

include(${CMAKE_CURRENT_LIST_DIR}/configure_warnings_and_errors.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/define_languages.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_instruction_set_architecture.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_operating_system.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_void_pointer_size.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_compiler.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/detect_multi_target_generator.cmake)

macro(begin_library)

  set(${name}.source_files "")
  set(${name}.header_files "")
  set(${name}.configuration_files "")

  define_languages(${name})
  detect_c_compiler(${name})
  detect_instruction_set_architecture(${name})
  detect_operating_system(${name})
  detect_multi_target_generator(${name})

endmacro()

macro(end_library)

  add_library(${name} STATIC)

  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/includes")
  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

  target_sources(${name} PRIVATE ${${name}.configuration_files} ${${name}.header_files} ${${name}.source_files})

  configure_warnings_and_errors(${name})
  
  if (${${name}.operating_system} STREQUAL ${${name}.operating_system_linux})
    set_property(TARGET ${name} PROPERTY POSITION_INDEPENDENT_CODE ON)
  endif()

endmacro()

macro(begin_executable)

  set(${name}.source_files "")
  set(${name}.header_files "")
  set(${name}.configuration_files "")

  define_languages(${name})
  detect_c_compiler(${name})
  detect_cpp_compiler(${name})
  detect_instruction_set_architecture(${name})
  detect_operating_system(${name})
  detect_multi_target_generator(${name})

endmacro()

macro(end_executable)

  add_executable(${name} ${${name}.configuration_files} ${${name}.header_files} ${${name}.source_files})

  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/includes")
  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

  configure_warnings_and_errors(${name})

endmacro()

macro(begin_plugin_library)

  set(${name}.source_files "")
  set(${name}.header_files "")
  set(${name}.configuration_files "")

  define_languages(${name})
  detect_c_compiler(${name})
  detect_cpp_compiler(${name})
  detect_instruction_set_architecture(${name})
  detect_operating_system(${name})
  detect_multi_target_generator(${name})

endmacro()

macro(end_plugin_library)

  add_library(${name} MODULE)

  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/includes")
  target_include_directories(${name} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")

  target_sources(${name} PRIVATE ${${name}.configuration_files} ${${name}.header_files} ${${name}.source_files})

  configure_warnings_and_errors(${name})

endmacro()
