#include "llvm/Transforms/Utils/LocalOptsPass.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Constants.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/Support/raw_ostream.h> 
#include <set> // Include set header

using namespace llvm;

bool runOnBasicBlock(BasicBlock &BB) {
    std::set<Instruction*> ToErase;
    bool Transformed = false;
    for (Instruction &Inst: BB) {
        outs() << "Instruction: " << Inst << "\n";
        // Algebraic Identity Optimization
        if (auto *BinOp = dyn_cast<BinaryOperator>(&Inst)) {
        outs() << "The instruction is a binary expression\n";
        Value *Operand0 = BinOp->getOperand(0);
        Value *Operand1 = BinOp->getOperand(1);
        Value *constantOperand = nullptr;
        Value *nonConstantOperand = nullptr;

        if((!isa<ConstantInt>(Operand0) && !isa<ConstantInt>(Operand1)) || (isa<ConstantInt>(Operand0) && isa<ConstantInt>(Operand1))){
            outs() << "Both or none operands are constants\n";
            continue;
        }

        if(isa<ConstantInt>(Operand0)){
            constantOperand = Operand0;
            nonConstantOperand = Operand1;
        } else if(isa<ConstantInt>(Operand1)){
            constantOperand = Operand1;
            nonConstantOperand = Operand0;
        }

        outs() << "Constant operand: ";
        constantOperand->print(outs());
        outs() << "\n";

        outs() << "Non-constant operand: ";
        nonConstantOperand->print(outs());
        outs() << "\n";

        if (BinOp->getOpcode() == Instruction::Add || BinOp->getOpcode() == Instruction::Sub || BinOp->getOpcode() == Instruction::FAdd || BinOp->getOpcode() == Instruction::FSub) {
            outs() << "The instruction is an Add or a Sub\n";
            if(cast<ConstantInt>(constantOperand)->isZero()){
            outs() << "The constant operand of the instruction is 0\n";
            Inst.replaceAllUsesWith(nonConstantOperand);
            outs() << "The uses of " << Inst << " have been replaced with ";
            nonConstantOperand->print(outs());
            outs() << "\n";
            ToErase.insert(&Inst);
            Transformed = true;
            continue;
            }
        } else if(BinOp->getOpcode() == Instruction::Mul || BinOp->getOpcode() == Instruction::FMul || BinOp->getOpcode() == Instruction::SDiv || BinOp->getOpcode() == Instruction::FDiv || BinOp->getOpcode() == Instruction::UDiv){
            outs() << "The instruction is a Mul or a Div\n";
            if(cast<ConstantInt>(constantOperand)->isOne()){
            outs() << "The constant operand of the instruction is 1\n";
            Inst.replaceAllUsesWith(nonConstantOperand);
            outs() << "The uses of " << Inst << " have been replaced with ";
            nonConstantOperand->print(outs());
            outs() << "\n";
            ToErase.insert(&Inst);
            Transformed = true;
            continue;
            }
        }

        // Strength Reduction Optimization
        ConstantInt *ConstOperand = cast<ConstantInt>(constantOperand);
        auto ConstValue = ConstOperand->getValue();

        if (BinOp->getOpcode() == Instruction::Mul) {
            outs() << "The instruction is a Mul\n";
            if (ConstValue.isPowerOf2()) {
            outs() << "The constant operand of the instruction is a power of 2\n";
            unsigned ShiftAmount = ConstValue.logBase2();
            Instruction *ShiftInst = BinaryOperator::Create(Instruction::Shl, nonConstantOperand, ConstantInt::get(nonConstantOperand->getType(), ShiftAmount));
            ShiftInst->insertAfter(&Inst);
            Inst.replaceAllUsesWith(ShiftInst);
            outs() << "The uses of " << Inst << " have been replaced with " << *ShiftInst << "\n";
            ToErase.insert(&Inst);
            Transformed = true;
            continue;
            } else if (ConstValue.countTrailingOnes() == ConstValue.popcount()) {
            outs() << "The constant operand of the instruction is NOT a power of 2\n";
            unsigned TotalSetBits = ConstValue.popcount();
            Instruction *ShiftInst = BinaryOperator::Create(Instruction::Shl, nonConstantOperand, ConstantInt::get(nonConstantOperand->getType(), TotalSetBits));
            ShiftInst->insertAfter(&Inst);
            Instruction *SubInst = BinaryOperator::Create(Instruction::Sub, ShiftInst, nonConstantOperand);
            SubInst->insertAfter(ShiftInst);
            Inst.replaceAllUsesWith(SubInst);
            outs() << "The uses of " << Inst << " have been replaced with " << *SubInst << "\n";
            ToErase.insert(&Inst);
            Transformed = true;
            continue;
            }else if(ConstValue[0] && ConstValue[ConstValue.getActiveBits()-1] && ConstValue.popcount() == 2){
                //exactly two bits set: the MSB and the LSB
                //shift amount: ConstValue.getActiveBits() - ConstValue.popcount() + 1 ==> ConstValue.getActiveBits() - 1
                Instruction *ShiftInst = BinaryOperator::Create(Instruction::Shl, nonConstantOperand, ConstantInt::get(nonConstantOperand->getType(), ConstValue.getActiveBits() - 1));
                ShiftInst->insertAfter(&Inst);
                Instruction *AddInst = BinaryOperator::Create(Instruction::Add, ShiftInst, nonConstantOperand);
                AddInst->insertAfter(ShiftInst);
                Inst.replaceAllUsesWith(AddInst);
                ToErase.insert(&Inst);
                Transformed = true;
                continue;
            }
        } else if ((BinOp->getOpcode() == Instruction::SDiv || BinOp->getOpcode() == Instruction::UDiv) && ConstOperand == Operand1) {
            outs() << "The instruction is a Div\n";
            if (ConstValue.isPowerOf2()) {
            outs() << "The constant operand of the instruction is a power of 2\n";
            unsigned ShiftAmount = ConstValue.logBase2();
            Instruction *ShiftInst = BinaryOperator::Create(Instruction::LShr, nonConstantOperand, ConstantInt::get(nonConstantOperand->getType(), ShiftAmount));
            ShiftInst->insertAfter(&Inst);
            Inst.replaceAllUsesWith(ShiftInst);
            outs() << "The uses of " << Inst << " have been replaced with " << *ShiftInst << "\n";
            ToErase.insert(&Inst);
            Transformed = true;
            continue;
            }
        }

        // Multi-Instruction Optimization
        for (auto iter = BinOp->use_begin(); iter != BinOp->use_end(); ++iter) {
            Instruction *I = dyn_cast<Instruction>(iter->getUser());

            if(auto *Op = dyn_cast<BinaryOperator>(I)) {
                outs() << "The user " << *I << " of the instruction " << Inst << " is a binary expression\n";
                if(BinOp->getOpcode() == Instruction::Add && Op->getOpcode() == Instruction::Sub && BinOp == Op->getOperand(0) && Op->getOperand(1) == constantOperand){
                    // a = b + 1; c = a - 1; ==> c = b;
                    I->replaceAllUsesWith(nonConstantOperand);
                    outs() << "The uses of " << *I << " have been replaced with ";
                    nonConstantOperand->print(outs());
                    outs() << "\n";
                    ToErase.insert(I);
                    Transformed = true;
                } else if(BinOp->getOpcode() == Instruction::Sub && constantOperand == Operand1 && Op->getOpcode() == Instruction::Add && (BinOp == Op->getOperand(0) || BinOp == Op->getOperand(1))){
                    // a = b - 1; c = a + 1; ==> c = b;
                    I->replaceAllUsesWith(nonConstantOperand);
                    outs() << "The uses of " << *I << " have been replaced with ";
                    nonConstantOperand->print(outs());
                    outs() << "\n";
                    ToErase.insert(I);
                    Transformed = true;
                } else if(BinOp->getOpcode() == Instruction::Mul && (Op->getOpcode() == Instruction::SDiv || Op->getOpcode() == Instruction::UDiv) && BinOp == Op->getOperand(0)){
                    // a = b * 3; c = a / 3; ==> c = b;
                    I->replaceAllUsesWith(nonConstantOperand);
                    outs() << "The uses of " << *I << " have been replaced with ";
                    nonConstantOperand->print(outs());
                    outs() << "\n";
                    ToErase.insert(I);
                    Transformed = true;
                } else if((BinOp->getOpcode() == Instruction::SDiv || BinOp->getOpcode() == Instruction::UDiv) && constantOperand == Operand1 && Op->getOpcode() == Instruction::Mul && (BinOp == Op->getOperand(0) || BinOp == Op->getOperand(1))){
                    // a = b / 3; c = a * 3; ==> c = b;
                    I->replaceAllUsesWith(nonConstantOperand);
                    outs() << "The uses of " << *I << " have been replaced with ";
                    nonConstantOperand->print(outs());
                    outs() << "\n";
                    ToErase.insert(I);
                    Transformed = true;
                }
            }
        }
    } 
  }
  
    for (auto *Inst : ToErase) {
        Inst->eraseFromParent();
    }
    ToErase.clear();

    return Transformed;
}

bool runOnFunction(Function &F) {
  bool Transformed = false;
  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    if (runOnBasicBlock(*Iter)) {
      Transformed = true;
    }
  }

  return Transformed;
}

PreservedAnalyses LocalOptsPass::run(Function &F, FunctionAnalysisManager &AM) {
  if (runOnFunction(F)) {
    return PreservedAnalyses::none();
  }
  return PreservedAnalyses::all();
}