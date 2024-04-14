/*
  Shizu Runtime
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

// EXIT_SUCCESS, EXIT_FAILURE
#include <stdlib.h>

#if 0
#include "idlib/experimental/process_mutex.private.h"
#include "idlib/experimental/system_signals.private.h"
#endif
#if 0
#include "idlib_network.h"
#endif

// fprintf, stderr
#include <stdio.h>

#include "Shizu/Runtime/Include.h"

void
run
  (
    Shizu_State* state
  )
{
#if 0
  // Initialize networking.
  if (idlib_network_startup()) {
    Shizu_State_setStatus(state, 1);
    Shizu_State_jump(state);
  }

  // Create the socket.
  idlib_socket* socket = NULL;
  if (idlib_create_socket(&socket)) {
    idlib_network_shutdown();
    Shizu_State_setStatus(state, 1);
    Shizu_State_jump(state);
  }

  // Destroy the socket.
  idlib_destroy_socket(socket);

  // Uninitialize networking.
  idlib_network_shutdown();
#endif
}

#if 0
static void
my_callback
  (
    void* context,
    idlib_system_signal system_signal
  )
{
  fprintf(stdout, "%s:%d: sigint\n", __FILE__, __LINE__);
  Shizu_State_setProcessExitRequested((Shizu_State*)context, Shizu_Boolean_True);
}
#endif

#include "idlib/process.h"

int
main
  (
    int argc,
    char **argv
  )
{
  int result = EXIT_SUCCESS;
  Shizu_State* state = NULL;
  if (Shizu_State_create(&state)) {
    result = EXIT_FAILURE;
    return result;
  }
  idlib_process* process = NULL;
  if (idlib_acquire_process(&process)) {
    Shizu_State_destroy(state);
    state = NULL;
    result = EXIT_FAILURE;
    return result;
  }
#if 0
  if (idlib_startup_system_signals()) {
    idlib_relinquish_process(process);
    process = NULL;
    Shizu_State_destroy(state);
    state = NULL;
    result = EXIT_FAILURE;
    return result;
  }
#endif
#if 0
  if (idlib_add_system_signals_callback(state, &my_callback)) {
    idlib_relinquish_process(process);
    process = NULL;
    Shizu_State_destroy(state);
    state = NULL;
    result = EXIT_FAILURE;
    return result;
  }
#endif
  Shizu_JumpTarget jumpTarget;
  Shizu_State_pushJumpTarget(state, &jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
  #if 0
    run(state);
    while (!Shizu_State_getProcessExitRequested(state)) {
    }
  #endif
    Shizu_State_popJumpTarget(state);
  } else {
    Shizu_State_popJumpTarget(state);
    result = EXIT_FAILURE;
  }
#if 0
  idlib_remove_system_signals_callback(state, &my_callback);
  idlib_process_shutdown();
#endif
#if 0
  idlib_shutdown_system_signals();
  idlib_shutdown_process_mutex();
#endif
  idlib_relinquish_process(process);
  process = NULL;
  Shizu_State_destroy(state);
  state = NULL;
  return result;
}
