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

#include "idlib/pipe.h"

// malloc, free
#include <malloc.h>

// memcpy
#include <string.h>

#include <stdio.h>

#include "idlib/array.h"

idlib_status idlib_pipe_message_create(idlib_pipe_message** RETURN, uint8_t const* p, size_t n) {
  if (!RETURN || !p) {
    return IDLIB_ARGUMENT_INVALID;
  }
  idlib_pipe_message* SELF = malloc(sizeof(idlib_pipe_message) + n);
  if (!SELF) {
    return IDLIB_ALLOCATION_FAILED;
  }
  memcpy(SELF->p, p, n);
  SELF->n = n;
  *RETURN = SELF;
  return IDLIB_SUCCESS;
}

idlib_status idlib_pipe_message_destroy(idlib_pipe_message* SELF) {
  if (!SELF) {
    return IDLIB_ARGUMENT_INVALID;
  }
  free(SELF);
  return IDLIB_SUCCESS;
}

#include <stdbool.h>

static idlib_status check_name(char const* name) {
  if (!name) {
    return IDLIB_ARGUMENT_INVALID;
  }
  const size_t max = 5012 - strlen("\\\\.\\pipe\\");
  size_t n = strlen(name);
  if (n == 0 || n > max) {
    return IDLIB_ARGUMENT_INVALID;
  }
  size_t i = 0;
  bool is = false;
  is |= ('a' <= name[i] && name[i] <= 'z') || ('A' <= name[i] && name[i] <= 'Z');
  is |= ('_' == name[i]);
  if (!is) {
    return IDLIB_ARGUMENT_INVALID;
  }
  i++;
  while (name[i] != '\0') {
    is = false;
    is |= ('a' <= name[i] && name[i] <= 'z') || ('A' <= name[i] && name[i] <= 'Z');
    is |= ('_' == name[i]);
    is |= ('0' <= name[i] && name[i] <= '9');
    if (!is) {
      return IDLIB_ARGUMENT_INVALID;
    }
    i++;
  };
  return IDLIB_SUCCESS;
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

idlib_status idlib_pipe_initialize_server(idlib_pipe* SELF, size_t messageBufferSize, char const* name) {
  if (!SELF) {
    return IDLIB_ARGUMENT_INVALID;
  }
  idlib_status status = check_name(name);
  if (status) {
    return status;
  }
  char buffer[5012 + 1];
  strcpy(buffer, "\\\\.\\pipe\\");
  strcat(buffer, name);
  HANDLE hPipe =
    CreateNamedPipe
      (
        buffer,
        PIPE_ACCESS_DUPLEX, // Full duplex (read and write) access.
        PIPE_TYPE_MESSAGE |
        PIPE_READMODE_MESSAGE |
        PIPE_NOWAIT, // Do not wait for messages. Fail if no message is available.
        PIPE_UNLIMITED_INSTANCES,  // unlimited number of instances 
        messageBufferSize, // The size of the output buffer.
        messageBufferSize, // The size of the input buffer.
        0,
        NULL
      );
  if (INVALID_HANDLE_VALUE == hPipe) {
    return IDLIB_ENVIRONMENT_FAILED;
  }
  SELF->pimpl = hPipe;
  return IDLIB_SUCCESS;
}

idlib_status idlib_pipe_initialize_client(idlib_pipe* SELF, char const* name) {
  if (!SELF) {
    return IDLIB_ARGUMENT_INVALID;
  }
  idlib_status status = check_name(name);
  if (status) {
    return status;
  }
  char buffer[5012 + 1];
  strcpy(buffer, "\\\\.\\pipe\\");
  strcat(buffer, name);
  HANDLE hPipe =
    CreateFile
      (
        buffer,  // pipe name 
        GENERIC_READ | // read and write access 
        GENERIC_WRITE,
        0, // no sharing 
        NULL, // default security attributes
        OPEN_EXISTING,  // opens existing pipe 
        0, // default attributes 
        NULL // no template file
      );
  if (INVALID_HANDLE_VALUE == hPipe) {
    return IDLIB_ENVIRONMENT_FAILED;
  }
  SELF->pimpl = hPipe;
  return IDLIB_SUCCESS;
}

idlib_status idlib_pipe_uninitialize(idlib_pipe* SELF) {
  CloseHandle(SELF->pimpl);
  SELF->pimpl = NULL;
  return IDLIB_SUCCESS;
}

idlib_status
idlib_pipe_read
(
  idlib_pipe_message** RETURN,
  idlib_pipe* pipe
) {
  idlib_status status;
  idlib_array_u8 buffer;
  status = idlib_array_u8_initialize(&buffer, 0);
  if (status) {
    fprintf(stderr, "%s:%d: unable to initialize buffer\n", __FILE__, __LINE__);
    return status;
  }
  while (true) {
    DWORD read1;
    char buffer1[1024];
    BOOL success =
      ReadFile
        (
          (HANDLE)pipe->pimpl, // pipe handle 
          buffer1, // buffer bytes 
          1024, // number of buffer bytes 
          &read1, // number of bytes read 
          NULL // not overlapped 
        );

  // Did we really receive an error?
    if (!success) {
      if (GetLastError() == ERROR_MORE_DATA) {
        // Append the available data and continue.
        status = idlib_array_u8_add_back_many(&buffer, buffer1, read1);
        if (status) {
          idlib_array_u8_uninitialize(&buffer);
          return status;
        }
        continue;
      } else if (GetLastError() == ERROR_PIPE_LISTENING) {
        // No writer is available.
        break;
      } else if (GetLastError() == ERROR_NO_DATA) {
        // No data is available.
        break;
      } else {
        // We do not consider ERROR_BROKEN_PIPE (the communication partner disconnected) not as an error.
        if (GetLastError() == ERROR_BROKEN_PIPE) {
          break;
        } else {
          fprintf(stderr, "%s:%d: read error: %ul\n", __FILE__, __LINE__, GetLastError());
          idlib_array_u8_uninitialize(&buffer);
          return 1;
        }
      }
    } else {
      // Append the available data and continue.
      status = idlib_array_u8_add_back_many(&buffer, buffer1, read1);
      if (status) {
        idlib_array_u8_uninitialize(&buffer);
        return status;
      }
      continue;
    }
  }
  uint8_t* p;
  size_t n;
  status = idlib_array_u8_get_bytes(&buffer, &p, &n);
  if (status) {
    idlib_array_u8_uninitialize(&buffer);
    return 1;
  }
  status = idlib_pipe_message_create(RETURN, p, n);
  idlib_array_u8_uninitialize(&buffer);
  return status;
}

idlib_status idlib_pipe_write(idlib_pipe* pipe, idlib_pipe_message* message) {
  DWORD written;
  BOOL success =
    WriteFile
    (
      (HANDLE)pipe->pimpl,// pipe handle 
      message->p, // message bytes 
      message->n, // number of message bytes 
      &written, // bytes written 
      NULL
    );
  if (!success) {
    return IDLIB_ENVIRONMENT_FAILED;
  }
  return IDLIB_SUCCESS;
}


