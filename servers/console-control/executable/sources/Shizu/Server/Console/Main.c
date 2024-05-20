/*
  Shizu
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

// EXIT_SUCCESS
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define MAXIMUM_MESSAGE_SIZE 5*16
#define PIPENAME "shizu_server_pipe"

// bool, true, false
#include <stdbool.h>
// fprintf, stdout, stderr
#include <stdio.h>
// uint8_t
#include <inttypes.h>

#include "idlib/pipe.h"

static uint8_t message_p[] = { 's', 'h', 'i', 'z', 'u' };
static size_t message_n = sizeof(message_p);

int
main
  (
    int argc,
    char **argv
  )
{
  idlib_pipe_message* message;
  idlib_pipe pipe;
  idlib_status status;
  status = idlib_pipe_initialize_client(&pipe, PIPENAME);
  if (status) {
    return EXIT_FAILURE;
  }
  status = idlib_pipe_message_create(&message, message_p, message_n);
  if (status) {
    fprintf(stderr, "%s:%d: write failed\n", __FILE__, __LINE__);
    idlib_pipe_uninitialize(&pipe);
    return EXIT_FAILURE;;
  }
  status = idlib_pipe_write(&pipe, message);
  idlib_pipe_message_destroy(message);
  if (status) {
    fprintf(stderr, "%s:%d: write failed\n", __FILE__, __LINE__);
    idlib_pipe_uninitialize(&pipe);
    return EXIT_FAILURE;;
  }
  idlib_pipe_uninitialize(&pipe);
  return EXIT_SUCCESS;
}
