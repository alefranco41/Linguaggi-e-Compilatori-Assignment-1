#include "LocalOpts.h"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Constants.h>

using namespace llvm;


bool runOnBasicBlock(BasicBlock &B) {
  bool Transformed = false;

  // Algebraic Identity Optimization
  for (auto &Inst : B) {
    if (auto *BinOp = dyn_cast<BinaryOperator>(&Inst)) {
      if (BinOp->getOpcode() == Instruction::Add || BinOp->getOpcode() == Instruction::Mul) {
        Value *Operand0 = BinOp->getOperand(0);
        Value *Operand1 = BinOp->getOperand(1);

        if (isa<ConstantInt>(Operand0) && cast<ConstantInt>(Operand0)->isZero()) {
          Transformed = true;
          BinOp->replaceAllUsesWith(Operand1);
          BinOp->eraseFromParent();
        } else if (isa<ConstantInt>(Operand1) && cast<ConstantInt>(Operand1)->isZero()) {
          Transformed = true;
          BinOp->replaceAllUsesWith(Operand0);
          BinOp->eraseFromParent();
        } else if (BinOp->getOpcode() == Instruction::Mul &&
                   ((isa<ConstantInt>(Operand0) && cast<ConstantInt>(Operand0)->isOne()) ||
                    (isa<ConstantInt>(Operand1) && cast<ConstantInt>(Operand1)->isOne()))) {
          Transformed = true;
          BinOp->replaceAllUsesWith(Operand0->getType()->isIntegerTy() ? Operand1 : Operand0);
          BinOp->eraseFromParent();
        }
      }
    }
  }

// Strength Reduction Optimization
for (auto &Inst : B) {
    if (auto *BinOp = dyn_cast<BinaryOperator>(&Inst)) {
        if (BinOp->getOpcode() == Instruction::Mul) {
            Value *Operand0 = BinOp->getOperand(0);
            Value *Operand1 = BinOp->getOperand(1);

            ConstantInt *ConstOperand = nullptr;
            Value *NonConstOperand = nullptr;

            if (auto *ConstOp = dyn_cast<ConstantInt>(Operand0)) {
                ConstOperand = ConstOp;
                NonConstOperand = Operand1;
            } else if (auto *ConstOp = dyn_cast<ConstantInt>(Operand1)) {
                ConstOperand = ConstOp;
                NonConstOperand = Operand0;
            }

            if (ConstOperand) {
                unsigned ShiftAmount = 0;
                if (ConstOperand->getValue().isPowerOf2()) {
                    ShiftAmount = ConstOperand->getValue().logBase2();
                } else {
                    // Se la costante non è una potenza di 2, trasformiamo in shift e somma
                    ShiftAmount = ConstOperand->getValue().getLimitedValue() - 1;
                }

                Transformed = true;
                Instruction *ShiftInst = BinaryOperator::Create(Instruction::Shl, NonConstOperand,
                                                                ConstantInt::get(NonConstOperand->getType(), ShiftAmount));
                Instruction *SubInst = BinaryOperator::Create(Instruction::Sub, ShiftInst, NonConstOperand);
                BinOp->replaceAllUsesWith(SubInst);
                BinOp->eraseFromParent();
            }
        }else if (BinOp->getOpcode() == Instruction::SDiv || BinOp->getOpcode() == Instruction::UDiv) {
            Value *Operand0 = BinOp->getOperand(0);
            Value *Operand1 = BinOp->getOperand(1);

            ConstantInt *ConstOperand = nullptr;
            Value *NonConstOperand = nullptr;

            if (auto *ConstOp = dyn_cast<ConstantInt>(Operand1)) {
                ConstOperand = ConstOp;
                NonConstOperand = Operand0;
            }

            if (ConstOperand) {
                unsigned ShiftAmount = ConstOperand->getValue().logBase2();
                
                Transformed = true;
                Instruction *ShiftInst = BinaryOperator::Create(Instruction::LShr, NonConstOperand,
                                                                ConstantInt::get(NonConstOperand->getType(), ShiftAmount));
                BinOp->replaceAllUsesWith(ShiftInst);
                BinOp->eraseFromParent();
            }
        }
    }
}


  // Multi-Instruction Optimization
  for (auto &Inst : B) {
    if (auto *Inst1 = dyn_cast<Instruction>(&Inst)) {
      if (auto *Inst2 = dyn_cast<Instruction>(Inst1->getNextNode())) {
        if (Inst1->hasOneUse() && Inst1->use_empty() && Inst2->getOperand(0) == Inst1) {
          Transformed = true;
          Inst1->replaceAllUsesWith(Inst2->getOperand(1));
          Inst1->eraseFromParent();
        }
      }
    }
  }

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


PreservedAnalyses LocalOpts::run(Module &M,
                                      ModuleAnalysisManager &AM) {
  for (auto Fiter = M.begin(); Fiter != M.end(); ++Fiter)
    if (runOnFunction(*Fiter))
      return PreservedAnalyses::none();
  
  return PreservedAnalyses::all();
}