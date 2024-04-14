/*
  Shizu Languages
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

#include "Shizu/Languages/Parser.h"

static Shizu_TypeDescriptor const Shizu_L1_Parser_Type = {
  .staticInitialize = NULL,
  .staticFinalize = NULL,
  .staticVisit = NULL,
  .size = sizeof(Shizu_L1_Parser),
  .visit = (Shizu_OnVisitCallback*)NULL,
  .finalize = (Shizu_OnFinalizeCallback*)NULL,
  .dispatchSize = sizeof(Shizu_L1_Parser_Dispatch),
  .dispatchInitialize = NULL,
  .dispatchUninitialize = NULL,
};

Shizu_defineType(Shizu_L1_Parser, Shizu_Object);

void
Shizu_L1_Parser_construct
  (
    Shizu_State* state,
    Shizu_L1_Parser* self
  )
{
  Shizu_Type* type = Shizu_L1_Parser_getType(state);
  ((Shizu_Object*)self)->type = type;
}

Shizu_L1_Parser*
Shizu_L1_Parser_create
  (
    Shizu_State* state
  )
{
  Shizu_L1_Parser* self = (Shizu_L1_Parser*)Shizu_Gc_allocate(state, sizeof(Shizu_L1_Parser));
  Shizu_L1_Parser_construct(state, self);
  return self;
}