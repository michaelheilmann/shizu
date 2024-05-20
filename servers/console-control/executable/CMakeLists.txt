#
# Shizu
# Copyright (C) 2024 Michael Heilmann. All rights reserved.
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

set(name ${Shizu.project-name}.ConsoleServerControl)

begin_executable()

list(APPEND ${name}.include_files includes/Shizu/Server/Console/Configure.h.in)
list(APPEND ${name}.source_files sources/Shizu/Server/Console/Main.c)

# Configuration variables for 'Configure.h.in'.
if (${${name}.operating_system} STREQUAL ${${name}.operating_system_windows})
  set(Shizu_Configuration_OperatingSystem Shizu_Configuration_OperatingSystem_Windows)
endif()
if (${${name}.operating_system} STREQUAL ${${name}.operating_system_linux})
  set(Shizu_Configuration_OperatingSystem Shizu_Configuration_OperatingSystem_Linux)
endif()

if (${${name}.compiler_c} STREQUAL ${${name}.compiler_c_msvc})
  set(Shizu_Configuration_CompilerC Shizu_Configuration_CompilerC_Msvc)
endif()
if (${${name}.compiler_c} STREQUAL ${${name}.compiler_c_gcc})
  set(Shizu_Configuration_CompilerC Shizu_Configuration_CompilerC_Gcc)
endif()

if (${${name}.instruction_set_architecture} EQUAL ${${name}.instruction_set_architecture_x64})
  set(Shizu_Configuration_InstructionSetArchitecture Shizu_Configuration_InstructionSetArchitecture_X64)
endif()
if (${${name}.instruction_set_architecture} EQUAL ${${name}.instruction_set_architecture_x86})
  set(Shizu_Configuration_InstructionSetArchitecture Shizu_Configuration_InstructionSetArchitecture_X86)
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/includes/Shizu/Server/Console/Configure.h.in includes/Shizu/Server/Console/Configure.h)
list(APPEND ${name}.sources includes/Shizu/Server/Console/Configure.h)

end_executable()

target_link_libraries(${name} Shizu.Runtime idlib-pipe idlib-process)

add_dependencies(${name} Shizu.Runtime.Modules.FileSystem)

set(modules "")
get_target_property(modules Shizu.Runtime modules)
foreach (module ${modules})
  add_dependencies(${name} ${module})
endforeach()

foreach (module ${modules})
  copy_plugin(${name} ${module})
endforeach()
