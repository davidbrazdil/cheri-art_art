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

#ifndef ART_COMPILER_DEX_QUICK_X86_CODEGEN_X86_H_
#define ART_COMPILER_DEX_QUICK_X86_CODEGEN_X86_H_

#include "dex/compiler_internals.h"
#include "x86_lir.h"

namespace art {

class X86Mir2Lir : public Mir2Lir {
  public:
    X86Mir2Lir(CompilationUnit* cu, MIRGraph* mir_graph, ArenaAllocator* arena);

    // Required for target - codegen helpers.
    bool SmallLiteralDivRem(Instruction::Code dalvik_opcode, bool is_div, RegLocation rl_src,
                                    RegLocation rl_dest, int lit);
    int LoadHelper(ThreadOffset offset);
    LIR* LoadBaseDisp(int rBase, int displacement, int r_dest, OpSize size, int s_reg);
    LIR* LoadBaseDispWide(int rBase, int displacement, int r_dest_lo, int r_dest_hi,
                                  int s_reg);
    LIR* LoadBaseIndexed(int rBase, int r_index, int r_dest, int scale, OpSize size);
    LIR* LoadBaseIndexedDisp(int rBase, int r_index, int scale, int displacement,
                                     int r_dest, int r_dest_hi, OpSize size, int s_reg);
    LIR* LoadConstantNoClobber(int r_dest, int value);
    LIR* LoadConstantWide(int r_dest_lo, int r_dest_hi, int64_t value);
    LIR* StoreBaseDisp(int rBase, int displacement, int r_src, OpSize size);
    LIR* StoreBaseDispWide(int rBase, int displacement, int r_src_lo, int r_src_hi);
    LIR* StoreBaseIndexed(int rBase, int r_index, int r_src, int scale, OpSize size);
    LIR* StoreBaseIndexedDisp(int rBase, int r_index, int scale, int displacement,
                                      int r_src, int r_src_hi, OpSize size, int s_reg);
    void MarkGCCard(int val_reg, int tgt_addr_reg);

    // Required for target - register utilities.
    bool IsFpReg(int reg);
    bool SameRegType(int reg1, int reg2);
    int AllocTypedTemp(bool fp_hint, int reg_class);
    int AllocTypedTempPair(bool fp_hint, int reg_class);
    int S2d(int low_reg, int high_reg);
    int TargetReg(SpecialTargetRegister reg);
    RegLocation GetReturnAlt();
    RegLocation GetReturnWideAlt();
    RegLocation LocCReturn();
    RegLocation LocCReturnDouble();
    RegLocation LocCReturnFloat();
    RegLocation LocCReturnWide();
    uint32_t FpRegMask();
    uint64_t GetRegMaskCommon(int reg);
    void AdjustSpillMask();
    void ClobberCallerSave();
    void FlushReg(int reg);
    void FlushRegWide(int reg1, int reg2);
    void FreeCallTemps();
    void FreeRegLocTemps(RegLocation rl_keep, RegLocation rl_free);
    void LockCallTemps();
    void MarkPreservedSingle(int v_reg, int reg);
    void CompilerInitializeRegAlloc();

    // Required for target - miscellaneous.
    void AssembleLIR();
    int AssignInsnOffsets();
    void AssignOffsets();
    AssemblerStatus AssembleInstructions(CodeOffset start_addr);
    void DumpResourceMask(LIR* lir, uint64_t mask, const char* prefix);
    void SetupTargetResourceMasks(LIR* lir, uint64_t flags);
    const char* GetTargetInstFmt(int opcode);
    const char* GetTargetInstName(int opcode);
    std::string BuildInsnString(const char* fmt, LIR* lir, unsigned char* base_addr);
    uint64_t GetPCUseDefEncoding();
    uint64_t GetTargetInstFlags(int opcode);
    int GetInsnSize(LIR* lir);
    bool IsUnconditionalBranch(LIR* lir);

    // Required for target - Dalvik-level generators.
    void GenArithImmOpLong(Instruction::Code opcode, RegLocation rl_dest,
                                   RegLocation rl_src1, RegLocation rl_src2);
    void GenArrayGet(int opt_flags, OpSize size, RegLocation rl_array,
                             RegLocation rl_index, RegLocation rl_dest, int scale);
    void GenArrayPut(int opt_flags, OpSize size, RegLocation rl_array,
                     RegLocation rl_index, RegLocation rl_src, int scale, bool card_mark);
    void GenShiftImmOpLong(Instruction::Code opcode, RegLocation rl_dest,
                           RegLocation rl_src1, RegLocation rl_shift);
    void GenMulLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenAddLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenAndLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenArithOpDouble(Instruction::Code opcode, RegLocation rl_dest,
                                  RegLocation rl_src1, RegLocation rl_src2);
    void GenArithOpFloat(Instruction::Code opcode, RegLocation rl_dest,
                                 RegLocation rl_src1, RegLocation rl_src2);
    void GenCmpFP(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1,
                          RegLocation rl_src2);
    void GenConversion(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src);
    bool GenInlinedCas(CallInfo* info, bool is_long, bool is_object);
    bool GenInlinedMinMaxInt(CallInfo* info, bool is_min);
    bool GenInlinedSqrt(CallInfo* info);
    bool GenInlinedPeek(CallInfo* info, OpSize size);
    bool GenInlinedPoke(CallInfo* info, OpSize size);
    void GenNegLong(RegLocation rl_dest, RegLocation rl_src);
    void GenOrLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenSubLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenXorLong(Instruction::Code opcode, RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    LIR* GenRegMemCheck(ConditionCode c_code, int reg1, int base, int offset,
                                ThrowKind kind);
    LIR* GenMemImmedCheck(ConditionCode c_code, int base, int offset, int check_value,
                          ThrowKind kind);
    RegLocation GenDivRem(RegLocation rl_dest, int reg_lo, int reg_hi, bool is_div);
    RegLocation GenDivRemLit(RegLocation rl_dest, int reg_lo, int lit, bool is_div);
    void GenCmpLong(RegLocation rl_dest, RegLocation rl_src1, RegLocation rl_src2);
    void GenDivZeroCheck(int reg_lo, int reg_hi);
    void GenEntrySequence(RegLocation* ArgLocs, RegLocation rl_method);
    void GenExitSequence();
    void GenFillArrayData(DexOffset table_offset, RegLocation rl_src);
    void GenFusedFPCmpBranch(BasicBlock* bb, MIR* mir, bool gt_bias, bool is_double);
    void GenFusedLongCmpBranch(BasicBlock* bb, MIR* mir);
    void GenSelect(BasicBlock* bb, MIR* mir);
    void GenMemBarrier(MemBarrierKind barrier_kind);
    void GenMoveException(RegLocation rl_dest);
    void GenMultiplyByTwoBitMultiplier(RegLocation rl_src, RegLocation rl_result,
                                               int lit, int first_bit, int second_bit);
    void GenNegDouble(RegLocation rl_dest, RegLocation rl_src);
    void GenNegFloat(RegLocation rl_dest, RegLocation rl_src);
    void GenPackedSwitch(MIR* mir, DexOffset table_offset, RegLocation rl_src);
    void GenSparseSwitch(MIR* mir, DexOffset table_offset, RegLocation rl_src);
    void GenSpecialCase(BasicBlock* bb, MIR* mir, const InlineMethod& special);
    /*
     * @brief Generate a two address long operation with a constant value
     * @param rl_dest location of result
     * @param rl_src constant source operand
     * @param op Opcode to be generated
     */
    void GenLongImm(RegLocation rl_dest, RegLocation rl_src, Instruction::Code op);
    /*
     * @brief Generate a three address long operation with a constant value
     * @param rl_dest location of result
     * @param rl_src1 source operand
     * @param rl_src2 constant source operand
     * @param op Opcode to be generated
     */
    void GenLongLongImm(RegLocation rl_dest, RegLocation rl_src1,
                        RegLocation rl_src2, Instruction::Code op);

    /**
      * @brief Generate a long arithmetic operation.
      * @param rl_dest The destination.
      * @param rl_src1 First operand.
      * @param rl_src2 Second operand.
      * @param op The DEX opcode for the operation.
      * @param is_commutative The sources can be swapped if needed.
      */
    void GenLongArith(RegLocation rl_dest, RegLocation rl_src1,
                      RegLocation rl_src2, Instruction::Code op, bool is_commutative);

    /**
      * @brief Generate a two operand long arithmetic operation.
      * @param rl_dest The destination.
      * @param rl_src Second operand.
      * @param op The DEX opcode for the operation.
      */
    void GenLongArith(RegLocation rl_dest, RegLocation rl_src, Instruction::Code op);

    /**
      * @brief Generate a long operation.
      * @param rl_dest The destination.  Must be in a register
      * @param rl_src The other operand.  May be in a register or in memory.
      * @param op The DEX opcode for the operation.
      */
    void GenLongRegOrMemOp(RegLocation rl_dest, RegLocation rl_src, Instruction::Code op);

    // Single operation generators.
    LIR* OpUnconditionalBranch(LIR* target);
    LIR* OpCmpBranch(ConditionCode cond, int src1, int src2, LIR* target);
    LIR* OpCmpImmBranch(ConditionCode cond, int reg, int check_value, LIR* target);
    LIR* OpCondBranch(ConditionCode cc, LIR* target);
    LIR* OpDecAndBranch(ConditionCode c_code, int reg, LIR* target);
    LIR* OpFpRegCopy(int r_dest, int r_src);
    LIR* OpIT(ConditionCode cond, const char* guide);
    LIR* OpMem(OpKind op, int rBase, int disp);
    LIR* OpPcRelLoad(int reg, LIR* target);
    LIR* OpReg(OpKind op, int r_dest_src);
    LIR* OpRegCopy(int r_dest, int r_src);
    LIR* OpRegCopyNoInsert(int r_dest, int r_src);
    LIR* OpRegImm(OpKind op, int r_dest_src1, int value);
    LIR* OpRegMem(OpKind op, int r_dest, int rBase, int offset);
    LIR* OpRegReg(OpKind op, int r_dest_src1, int r_src2);
    LIR* OpCondRegReg(OpKind op, ConditionCode cc, int r_dest, int r_src);
    LIR* OpRegRegImm(OpKind op, int r_dest, int r_src1, int value);
    LIR* OpRegRegReg(OpKind op, int r_dest, int r_src1, int r_src2);
    LIR* OpTestSuspend(LIR* target);
    LIR* OpThreadMem(OpKind op, ThreadOffset thread_offset);
    LIR* OpVldm(int rBase, int count);
    LIR* OpVstm(int rBase, int count);
    void OpLea(int rBase, int reg1, int reg2, int scale, int offset);
    void OpRegCopyWide(int dest_lo, int dest_hi, int src_lo, int src_hi);
    void OpTlsCmp(ThreadOffset offset, int val);

    void OpRegThreadMem(OpKind op, int r_dest, ThreadOffset thread_offset);
    void SpillCoreRegs();
    void UnSpillCoreRegs();
    static const X86EncodingMap EncodingMap[kX86Last];
    bool InexpensiveConstantInt(int32_t value);
    bool InexpensiveConstantFloat(int32_t value);
    bool InexpensiveConstantLong(int64_t value);
    bool InexpensiveConstantDouble(int64_t value);

    RegLocation UpdateLocWide(RegLocation loc);
    RegLocation EvalLocWide(RegLocation loc, int reg_class, bool update);
    RegLocation EvalLoc(RegLocation loc, int reg_class, bool update);
    int AllocTempDouble();
    void ResetDefLocWide(RegLocation rl);

  private:
    void EmitPrefix(const X86EncodingMap* entry);
    void EmitOpcode(const X86EncodingMap* entry);
    void EmitPrefixAndOpcode(const X86EncodingMap* entry);
    void EmitDisp(uint8_t base, int disp);
    void EmitModrmDisp(uint8_t reg_or_opcode, uint8_t base, int disp);
    void EmitModrmSibDisp(uint8_t reg_or_opcode, uint8_t base, uint8_t index, int scale, int disp);
    void EmitImm(const X86EncodingMap* entry, int imm);
    void EmitOpRegOpcode(const X86EncodingMap* entry, uint8_t reg);
    void EmitOpReg(const X86EncodingMap* entry, uint8_t reg);
    void EmitOpMem(const X86EncodingMap* entry, uint8_t base, int disp);
    void EmitOpArray(const X86EncodingMap* entry, uint8_t base, uint8_t index,
                     int scale, int disp);
    void EmitMemReg(const X86EncodingMap* entry, uint8_t base, int disp, uint8_t reg);
    void EmitMemImm(const X86EncodingMap* entry, uint8_t base, int disp, int32_t imm);
    void EmitRegMem(const X86EncodingMap* entry, uint8_t reg, uint8_t base, int disp);
    void EmitRegArray(const X86EncodingMap* entry, uint8_t reg, uint8_t base, uint8_t index,
                      int scale, int disp);
    void EmitArrayReg(const X86EncodingMap* entry, uint8_t base, uint8_t index, int scale, int disp,
                      uint8_t reg);
    void EmitRegThread(const X86EncodingMap* entry, uint8_t reg, int disp);
    void EmitRegReg(const X86EncodingMap* entry, uint8_t reg1, uint8_t reg2);
    void EmitRegRegImm(const X86EncodingMap* entry, uint8_t reg1, uint8_t reg2, int32_t imm);
    void EmitRegRegImmRev(const X86EncodingMap* entry, uint8_t reg1, uint8_t reg2, int32_t imm);
    void EmitRegMemImm(const X86EncodingMap* entry, uint8_t reg1, uint8_t base, int disp, int32_t imm);
    void EmitRegImm(const X86EncodingMap* entry, uint8_t reg, int imm);
    void EmitThreadImm(const X86EncodingMap* entry, int disp, int imm);
    void EmitMovRegImm(const X86EncodingMap* entry, uint8_t reg, int imm);
    void EmitShiftRegImm(const X86EncodingMap* entry, uint8_t reg, int imm);
    void EmitShiftRegCl(const X86EncodingMap* entry, uint8_t reg, uint8_t cl);
    void EmitRegCond(const X86EncodingMap* entry, uint8_t reg, uint8_t condition);

    /**
     * @brief Used for encoding conditional register to register operation.
     * @param entry The entry in the encoding map for the opcode.
     * @param reg1 The first physical register.
     * @param reg2 The second physical register.
     * @param condition The condition code for operation.
     */
    void EmitRegRegCond(const X86EncodingMap* entry, uint8_t reg1, uint8_t reg2, uint8_t condition);

    void EmitJmp(const X86EncodingMap* entry, int rel);
    void EmitJcc(const X86EncodingMap* entry, int rel, uint8_t cc);
    void EmitCallMem(const X86EncodingMap* entry, uint8_t base, int disp);
    void EmitCallThread(const X86EncodingMap* entry, int disp);
    void EmitPcRel(const X86EncodingMap* entry, uint8_t reg, int base_or_table, uint8_t index,
                   int scale, int table_or_disp);
    void EmitMacro(const X86EncodingMap* entry, uint8_t reg, int offset);
    void EmitUnimplemented(const X86EncodingMap* entry, LIR* lir);
    void GenFusedLongCmpImmBranch(BasicBlock* bb, RegLocation rl_src1,
                                  int64_t val, ConditionCode ccode);
    void OpVectorRegCopyWide(uint8_t fp_reg, uint8_t low_reg, uint8_t high_reg);
    void GenConstWide(RegLocation rl_dest, int64_t value);

    /*
     * @brief Return the correct x86 opcode for the Dex operation
     * @param op Dex opcode for the operation
     * @param loc Register location of the operand
     * @param is_high_op 'true' if this is an operation on the high word
     * @param value Immediate value for the operation.  Used for byte variants
     * @returns the correct x86 opcode to perform the operation
     */
    X86OpCode GetOpcode(Instruction::Code op, RegLocation loc, bool is_high_op, int32_t value);

    /*
     * @brief Return the correct x86 opcode for the Dex operation
     * @param op Dex opcode for the operation
     * @param dest location of the destination.  May be register or memory.
     * @param rhs Location for the rhs of the operation.  May be in register or memory.
     * @param is_high_op 'true' if this is an operation on the high word
     * @returns the correct x86 opcode to perform the operation
     * @note at most one location may refer to memory
     */
    X86OpCode GetOpcode(Instruction::Code op, RegLocation dest, RegLocation rhs,
                        bool is_high_op);

    /*
     * @brief Is this operation a no-op for this opcode and value
     * @param op Dex opcode for the operation
     * @param value Immediate value for the operation.
     * @returns 'true' if the operation will have no effect
     */
    bool IsNoOp(Instruction::Code op, int32_t value);

    /*
     * @brief Dump a RegLocation using printf
     * @param loc Register location to dump
     */
    static void DumpRegLocation(RegLocation loc);

    /**
     * @brief Calculate magic number and shift for a given divisor
     * @param divisor divisor number for calculation
     * @param magic hold calculated magic number
     * @param shift hold calculated shift
     */
    void CalculateMagicAndShift(int divisor, int& magic, int& shift);

    /*
     * @brief Generate an integer div or rem operation.
     * @param rl_dest Destination Location.
     * @param rl_src1 Numerator Location.
     * @param rl_src2 Divisor Location.
     * @param is_div 'true' if this is a division, 'false' for a remainder.
     * @param check_zero 'true' if an exception should be generated if the divisor is 0.
     */
    RegLocation GenDivRem(RegLocation rl_dest, RegLocation rl_src1,
                                  RegLocation rl_src2, bool is_div, bool check_zero);

    /*
     * @brief Generate an integer div or rem operation by a literal.
     * @param rl_dest Destination Location.
     * @param rl_src Numerator Location.
     * @param lit Divisor.
     * @param is_div 'true' if this is a division, 'false' for a remainder.
     */
    RegLocation GenDivRemLit(RegLocation rl_dest, RegLocation rl_src, int lit, bool is_div);

    /*
     * Generate code to implement long shift operations.
     * @param opcode The DEX opcode to specify the shift type.
     * @param rl_dest The destination.
     * @param rl_src The value to be shifted.
     * @param shift_amount How much to shift.
     * @returns the RegLocation of the result.
     */
    RegLocation GenShiftImmOpLong(Instruction::Code opcode, RegLocation rl_dest,
                                  RegLocation rl_src, int shift_amount);
    /*
     * Generate an imul of a register by a constant or a better sequence.
     * @param dest Destination Register.
     * @param src Source Register.
     * @param val Constant multiplier.
     */
    void GenImulRegImm(int dest, int src, int val);
    /*
     * Generate an imul of a memory location by a constant or a better sequence.
     * @param dest Destination Register.
     * @param sreg Symbolic register.
     * @param displacement Displacement on stack of Symbolic Register.
     * @param val Constant multiplier.
     */
    void GenImulMemImm(int dest, int sreg, int displacement, int val);
};

}  // namespace art

#endif  // ART_COMPILER_DEX_QUICK_X86_CODEGEN_X86_H_
