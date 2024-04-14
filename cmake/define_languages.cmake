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

# Macro to define an enumeration of languages.
#
# The enumeration constants ${target}.language_(unknown|c|cpp|masm) are defined.
# Each constant is a string of an unique name identifying a language.
#
# @param target The target.
macro(define_languages target)
  # Unknown language.
  set(${target}.language_unknown "<unknown language>")
  # The "C" language.
  set(${target}.language_c "C")
  # The "C++" language.
  set(${target}.language_cpp "CPP")
  # The "MASM" language.
  set(${target}.language_masm "MASM")
endmacro()
