/*
  IdLib Pipe
  Copyright (C) 2024 Michael Heilmann. All rights reserved.

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#if !defined(IDLIB_PIPE_H_INCLUDED)
#define IDLIB_PIPE_H_INCLUDED

#include "idlib/process.h"

typedef struct idlib_pipe_message {
  size_t n;
  uint8_t p[];
} idlib_pipe_message;

idlib_status idlib_pipe_message_create(idlib_pipe_message** RETURN, uint8_t const* p, size_t n);

idlib_status idlib_pipe_message_destroy(idlib_pipe_message* SELF);

typedef struct idlib_pipe {
  void* pimpl;
} idlib_pipe;

/// @brief Create a pipe server.
/// @param pipe A pointer to a <code>idlib_pipe</code> object.
/// @param name A pointer to a C string. The name of the pipe.
/// @return #IDLIB_SUCCESS on success. A non-zero status value on failure.
/// @error #IDLIB_ARGUMENT_INVALID @a pipe is a null pointer.
/// @error #IDLIB_ARGUMENT_INVALID @a name is a null pointer.
/// @error #IDLIB_ALLOCATION_FAILED an allocation failed.
/// @error #IDLIB_ENVIRONMENT_FAILED the environment failed.
idlib_status idlib_pipe_initialize_server(idlib_pipe* SELF, size_t maximumMessageSize, char const* name);

/// @brief Create a pipe client.
/// @param pipe A pointer to a <code>idlib_pipe</code> object.
/// @param name A pointer to a C string. The name of the pipe.
/// @return #IDLIB_SUCCESS on success. A non-zero status value on failure.
/// @error #IDLIB_ARGUMENT_INVALID @a pipe is a null pointer.
/// @error #IDLIB_ARGUMENT_INVALID @a name is a null pointer.
/// @error #IDLIB_ALLOCATION_FAILED an allocation failed.
/// @error #IDLIB_ENVIRONMENT_FAILED the environment failed.
idlib_status idlib_pipe_initialize_client(idlib_pipe* SELF, char const* name);

/// @brief Destroy a pipe (server or client).
/// @param pip A pointer to a <code>idlib_pipe</code> object.
/// @return #IDLIB_SUCCESS on success. A non-zero status value on failure.
/// @error #IDLIB_ARGUMENT_INVALID @a pipe is a null pointer.
idlib_status idlib_pipe_uninitialize(idlib_pipe* SELF);

/// @brief Read a message from a pipe.
/// @param RETURN [out] A pointer to a <code>idlib_pipe_message*</code> variable.
/// @param pipe A pointer to the pipe.
/// @return #IDLIB_SUCCESS on succeess.
/// A non-zero status value on failure.
/// @success <code>*RETURN</code> was assigned
/// - a pointer to the message if a message is available
/// - the null pointer if no message is available
/// @error #IDLIB_ARGUMENT_INVALID @a RETURN is a null pointer.
/// @error #IDLIB_ARGUMENT_INVALID @a pipe is a null pointer.
idlib_status
idlib_pipe_read
  (
    idlib_pipe_message** RETURN,
    idlib_pipe* pipe
  );

/// @brief Write a message to a pipe.
/// @param pipe A pointer to the pipe.
/// @param message A pointert to the message.
/// @return #IDLIB_SUCCESS on succeess.
/// A non-zero status value on failure.
/// @error #IDLIB_ARGUMENT_INVALID @a pipe is a null pointer.
/// @error #IDLIB_ARGUMENT_INVALID @a message is a null pointer.
idlib_status
idlib_pipe_write
  (
    idlib_pipe* pipe,
    idlib_pipe_message* message
  );

#endif // IDLIB_PIPE_H_INCLUDED
