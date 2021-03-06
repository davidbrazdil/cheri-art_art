/*
 * Copyright (C) 2011 The Android Open Source Project
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

#ifndef ART_RUNTIME_ASM_SUPPORT_H_
#define ART_RUNTIME_ASM_SUPPORT_H_

// Value loaded into rSUSPEND for quick. When this value is counted down to zero we do a suspend
// check.
#define SUSPEND_CHECK_INTERVAL (1000)

// Offsets within java.lang.Object.
#define CLASS_OFFSET 0
#define LOCK_WORD_OFFSET 4

// Offsets within java.lang.Class.
#define CLASS_COMPONENT_TYPE_OFFSET 12

// Array offsets.
#define ARRAY_LENGTH_OFFSET 8
#define OBJECT_ARRAY_DATA_OFFSET 12

// Offsets within java.lang.String.
#define STRING_VALUE_OFFSET 8
#define STRING_COUNT_OFFSET 12
#define STRING_OFFSET_OFFSET 20
#define STRING_DATA_OFFSET 12

// Offsets within java.lang.Method.
#define METHOD_DEX_CACHE_METHODS_OFFSET 12
#define METHOD_CODE_OFFSET 36

#endif  // ART_RUNTIME_ASM_SUPPORT_H_
