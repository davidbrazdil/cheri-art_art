/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_RUNTIME_ARCH_ARM_ASM_SUPPORT_ARM_H_
#define ART_RUNTIME_ARCH_ARM_ASM_SUPPORT_ARM_H_

#include "asm_support.h"

// Register holding suspend check count down.
#define rSUSPEND r4
// Register holding Thread::Current().
#define rSELF r9
// Offset of field Thread::suspend_count_ verified in InitCpu
#define THREAD_FLAGS_OFFSET 0
// Offset of field Thread::card_table_ verified in InitCpu
#define THREAD_CARD_TABLE_OFFSET 8
// Offset of field Thread::exception_ verified in InitCpu
#define THREAD_EXCEPTION_OFFSET 12
// Offset of field Thread::thin_lock_thread_id_ verified in InitCpu
#define THREAD_ID_OFFSET 60

#endif  // ART_RUNTIME_ARCH_ARM_ASM_SUPPORT_ARM_H_
