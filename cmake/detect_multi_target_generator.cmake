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

# Macro to detect a multi target generator is used.
# Set ${target}.is_multi_target_generator to "YES" (a multi target generator is used) or "NO" (a single target generator is used).
# @param target The target.
macro(detect_multi_target_generator target)
  if (NOT DEFINED ${target}.compiler_c)
    message(FATAL_ERROR "please execute detect_compiler before detect_multi_target_generator")
  endif()
  if (${target}.compiler_c STREQUAL ${target}.compiler_c_msvc)
    set(${target}.is_multi_target_generator YES)
  else()
    set(${target}.is_multi_target_generator NO)
  endif()
  message(STATUS " - ${target} multi-target generator: ${${target}.is_multi_target_generator}")
endmacro(detect_multi_target_generator)
