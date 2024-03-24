/*
  Arnamsneat - A SDL based GUI toolkit.
  Copyright (C) 2024 Vadim Nikolaev (https://github.com/vadniks).

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#pragma once

#include "../include/arnamsneatPrivate.h"
#include <stddef.h>

#define defsAtomic _Atomic
#define DEFS_USED(x) ((void) x)

void defsAssert(bool condition);
bool defsSuccessful(int result);
void* AMST_NONNULL defsMalloc(size_t size);
void* AMST_NONNULL defsRealloc(void* AMST_NULLABLE memory, size_t size);
void defsFree(void* AMST_NULLABLE memory);
