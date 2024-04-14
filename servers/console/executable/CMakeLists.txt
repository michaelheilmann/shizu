# Copyright (c) 2024 Michael Heilmann. All rights reserved.

cmake_minimum_required(VERSION 3.20)

set(name ${Shizu.project-name}.ConsoleServer)

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

target_link_libraries(${name} Shizu.Runtime idlib-process)
