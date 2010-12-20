//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "SUPER"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
using namespace llvm;

STATISTIC(HelloCounter, "Counts number of basic block greeted");

namespace {
  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct SuperOptPass : public BasicBlockPass {
    static char ID; // Pass identification, replacement for typeid
    SuperOptPass() : BasicBlockPass(ID) {}

    virtual bool runOnBasicBlock(BasicBlock &BB) {
      bool modified=false;  
      ++HelloCounter;
      errs() << "Hello: ";
      errs().write_escaped(BB.getName()) << '\n';

      for(BasicBlock::iterator I=BB.begin(), E=BB.end(); I!=E; ++I) {
        errs() << I->getOpcode() << '\n'; 
      }

      return modified;
    }

    // We don't modify the program, so we preserve all analyses
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesAll();
    }
  };
}

char SuperOptPass::ID = 0;
INITIALIZE_PASS(SuperOptPass, "super",
                "superoptimizer",
                false, false);
