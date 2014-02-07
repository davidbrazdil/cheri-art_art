/*
 * Copyright (C) 2012 The Android Open Source Project
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

#include "asm_support_mips.S"

#include "arch/quick_alloc_entrypoints.S"

    .set noreorder
    .balign 8

    /*
     * On entry $a0 is uint64_t* gprs_ and $a1 is uint32_t* fprs_
     * FIXME: just guessing about the shape of the jmpbuf.  Where will pc be?
     */
ENTRY art_quick_do_long_jump
    l.s     $f0, 0($a1)
    l.s     $f1, 4($a1)
    l.s     $f2, 8($a1)
    l.s     $f3, 12($a1)
    l.s     $f4, 16($a1)
    l.s     $f5, 20($a1)
    l.s     $f6, 24($a1)
    l.s     $f7, 28($a1)
    l.s     $f8, 32($a1)
    l.s     $f9, 36($a1)
    l.s     $f10, 40($a1)
    l.s     $f11, 44($a1)
    l.s     $f12, 48($a1)
    l.s     $f13, 52($a1)
    l.s     $f14, 56($a1)
    l.s     $f15, 60($a1)
    l.s     $f16, 64($a1)
    l.s     $f17, 68($a1)
    l.s     $f18, 72($a1)
    l.s     $f19, 76($a1)
    l.s     $f20, 80($a1)
    l.s     $f21, 84($a1)
    l.s     $f22, 88($a1)
    l.s     $f23, 92($a1)
    l.s     $f24, 96($a1)
    l.s     $f25, 100($a1)
    l.s     $f26, 104($a1)
    l.s     $f27, 108($a1)
    l.s     $f28, 112($a1)
    l.s     $f29, 116($a1)
    l.s     $f30, 120($a1)
    l.s     $f31, 124($a1)
    ld      $at, 8($a0)
    ld      $v0, 16($a0)
    ld      $v1, 24($a0)
    ld      $a1, 40($a0)
    ld      $a2, 48($a0)
    ld      $a3, 56($a0)
    ld      $t0, 64($a0)
    ld      $t1, 72($a0)
    ld      $t2, 80($a0)
    ld      $t3, 88($a0)
    ld      $t4, 96($a0)
    ld      $t5, 104($a0)
    ld      $t6, 112($a0)
    ld      $t7, 120($a0)
    ld      $s0, 128($a0)
    ld      $s1, 136($a0)
    ld      $s2, 144($a0)
    ld      $s3, 152($a0)
    ld      $s4, 160($a0)
    ld      $s5, 168($a0)
    ld      $s6, 176($a0)
    ld      $s7, 184($a0)
    ld      $t8, 192($a0)
    ld      $t9, 200($a0)
    ld      $k0, 208($a0)
    ld      $k1, 216($a0)
    ld      $gp, 224($a0)
    ld      $sp, 232($a0)
    ld      $fp, 240($a0)
    ld      $ra, 248($a0)
    ld      $a0, 32($a0)
    move    $v0, $zero          # clear result registers r0 and r1
    jr      $ra                 # do long jump
    move    $v1, $zero
END art_quick_do_long_jump

