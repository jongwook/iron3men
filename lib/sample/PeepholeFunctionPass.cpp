/*
 * EECS 583 F2010 Homework 1 - Dong Young Yoon, UMID: 3226 6816
 * llvm-gcc version used: gcc version 4.2.1 (Based on Apple Inc. build 5658) (LLVM build)
 * g++ version used: gcc version 4.4.3 (Ubuntu 4.4.3-4ubuntu5)
 * LLVM 2.7 used.
 */ 
#define DEBUG_TYPE "peephole-opt-func-pass"
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Analysis/ProfileInfoLoader.h"
#include "llvm/InstrTypes.h"
using namespace llvm;

namespace {

  struct PeepholeFunctionPass : public FunctionPass {
//    ProfileInfo *pInfo;
    static bool header;
    static char ID; // Pass identification, replacement for typeid
    
    PeepholeFunctionPass() : FunctionPass(ID) {}
     
    virtual bool runOnFunction(Function &F) {
      
      Function::iterator func_it;
      BasicBlock::iterator bb_it;
      
      for (func_it=F.begin();func_it!=F.end();++func_it)
      {
      	for (bb_it=func_it->begin();bb_it!=func_it->end();++bb_it)
      	{
      	    
      	}
      }
      
      return false;
    }
     
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesCFG(); 
    //  AU.addRequired<ProfileInfo>();
    }
  };
}

char PeepholeFunctionPass::ID = 3;
INITIALIZE_PASS(PeepholeFunctionPass, "peephole-opts",
                "Peephole Optimizer Function Pass", false, false);
bool PeepholeFunctionPass::header = false; 
//static RegisterPass<PeepholeFunctionPass> ds ("peephole_opt_func_pass", "Peephole Optimizer Function Pass");

