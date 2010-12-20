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

#include <list>
#include "llvm/Pass.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Constants.h"
#include "llvm/InstrTypes.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/LLVMContext.h"
#include "InstCombination.h"
#include "SmallFunction.h"

using namespace llvm;

static bool supported(int opcode) {
	return opcode==8 || opcode==10 || opcode==12 || opcode==20;
}

static void printFunc(std::vector<InstTemplate> &list) {
	for(unsigned int i=0;i<list.size();++i) {
		errs() << list[i].toString() << '\n';
	}
}

namespace {
	// Hello2 - The second implementation with getAnalysisUsage implemented.
  struct SuperOptPass : public BasicBlockPass {
    static char ID; // Pass identification, replacement for typeid
    SuperOptPass() : BasicBlockPass(ID) {}
		std::vector<Instruction *> result;

		std::vector<Instruction *>* superOptimize(std::list<Instruction *> &func, std::set<Instruction *> &input) {
			std::map<Instruction *, char> dict;
			std::map<char, Instruction *> inv;
			std::vector<InstTemplate> model;

			result.clear();

			char name='A';
			for(std::set<Instruction *>::iterator it=input.begin(); it!=input.end(); ++it) {
				dict[*it]=name;
				inv[name]=*it;
				//errs() << ((int)(*it))%1000 << '-' << name << '\n';
				name++;
			}
			
			name='a';
			for(std::list<Instruction *>::iterator it=func.begin(); it!=func.end(); ++it) {
				dict[*it]=name;
				inv[name]=*it;
				//errs() << ((int)(*it))%1000 << '-' << name;
				name++;
				
				std::stringstream ss;
				ss << (*it)->getOpcodeName();
				if((*it)->getNumOperands()!=2) {
					errs() << "ERROR: numOperand not 2\n";
					return NULL;
				}

				for(unsigned int i=0; i<(*it)->getNumOperands(); ++i) {
					Value *operand=(*it)->getOperand(i);
					if(Instruction::classof(operand)) {
						if(!dict.count((Instruction *)operand)) {
							errs() << "ERROR: " << ((int)(*it)%1000) << "- operand " << ((int)((*it)->getOperand(i))%1000) << " not found in dictionary\n";
							return NULL;
						}
						ss << " " << dict[(Instruction *)(*it)->getOperand(i)];
					} else if (ConstantInt::classof(operand)) {
						ConstantInt *value=(ConstantInt *)operand;
						ss << " " << value->getValue().getLimitedValue();
					}
				}
				model.push_back(InstTemplate(ss.str()));
				//errs() << ": " << ss.str() << '\n';
			}

			SmallFunction modelfunc(model);

			bool done=false;
			for(unsigned int length=1; length<func.size() && !done; ++length) {
				for(InstCombination combi(input.size(),length); !combi.invalid && !done; combi.next()) {
					std::vector<InstTemplate> list(combi.list, combi.list+combi.length);
					SmallFunction test(list);
					if(modelfunc == test) {
						done = true;
						errs() << "This code :\n";
						printFunc(model);
						errs() << "changed to a simpler version : \n";
						printFunc(list);
						
						// construct instructions
						Instruction **internals=new Instruction *[length];
						for(unsigned int i=0; i<length; ++i) {
							Instruction *inst;
							Value *op1, *op2;
							if(list[i].operands[0].isVariable()) {
								op1=inv[list[i].operands[0].type];
							} else if(list[i].operands[0].isInternal()) {
								op1=internals[list[i].operands[0].type-'a'];
							} else {
								op1=ConstantInt::get(getGlobalContext(), APInt(32,list[i].operands[0].value,true));
							}
							if(list[i].operands[1].isVariable()) {
								op2=inv[list[i].operands[1].type];
							} else if(list[i].operands[1].isInternal()) {
								op2=internals[list[i].operands[1].type-'a'];
							} else {
								op2=ConstantInt::get(getGlobalContext(), APInt(32,list[i].operands[1].value,true));
							}
							
							switch(list[i].opcode) {
								case 8:	// add
									inst=BinaryOperator::CreateNSWAdd(op1,op2);
									break;
								case 10:	// sub
									inst=BinaryOperator::CreateNSWSub(op1,op2);
									break;
								case 12:	// mul
									inst=BinaryOperator::CreateNSWMul(op1,op2);
									break;
								default:
									errs () << "ERROR : unknown upcode\n";
									inst=NULL;
							}
							internals[i]=inst;
							result.push_back(inst);
						}

						delete [] internals;
						return &result;
					}
				}
			}
		
			return NULL;
		}

    virtual bool runOnBasicBlock(BasicBlock &BB) {
      bool modified=false;  

			std::vector<Instruction *> targets;
			std::map<Instruction *, std::vector<Instruction *> *> backref;
			for(BasicBlock::iterator I=BB.begin(), E=BB.end(); I!=E; ++I) {
				backref[&(*I)]=new std::vector<Instruction *>;
			}

      for(BasicBlock::iterator I=BB.begin(), E=BB.end(); I!=E; ++I) {
				//errs() << ((int)&(*I))%1000 << ' ' << I->getOpcodeName();
				if(I->hasOneUse() && I->use_back()->getParent() == &BB) {
					//errs() << " oneuse";
					if(supported(I->getOpcode())) {
						targets.push_back(&(*I));
					}
				}
				for(Instruction::use_iterator U=I->use_begin(), E=I->use_end(); U!=E; ++U) {
					backref[(Instruction *)(*U)]->push_back(&(*I));
				}
				//errs() << '\n';
      }

			for(unsigned int i=0;i<targets.size();++i) {
			  // populate backref list
				Instruction *root=targets[i];
				// errs() << ((int)root)%10000 << root->getOpcodeName() << "--------\n";
				std::list<Instruction *> backrefs;
				std::set<Instruction *> tempset, used, input;
				backrefs.push_front(root);
				tempset.insert(root);
				while(!tempset.empty()) {
					Instruction *inst = *tempset.begin();
					tempset.erase(inst);
					used.insert(inst);
					for(std::vector<Instruction *>::iterator it=backref[inst]->begin(); it!=backref[inst]->end(); ++it) {
						Instruction *back = *it;
						if(used.count(back) || tempset.count(back)) continue;
						if(supported(back->getOpcode())) {
							backrefs.push_front(back);
							tempset.insert(back);
						} else {
							input.insert(back);
						}
					}

				}

				// now populated

				// only if it is more than or equal to 3
				if(backrefs.size()>=3) {
					std::vector<Instruction *> *result=superOptimize(backrefs, input);
					if(result) {
						// find the resulting instruction and replace with the new root
						Instruction *newroot=result->at(result->size()-1);
						Instruction *next=root->use_back();
						for(unsigned int i=0; i<next->getNumOperands(); ++i) {
							if(next->getOperand(i)==root) {
								next->setOperand(i,newroot);
							}
						}

						// add new insts
						for(unsigned int i=0; i<result->size(); ++i) {
							result->at(i)->insertBefore(next);
						}

						// delete old backrefs 
						for(std::list<Instruction *>::iterator it=backrefs.begin(); it!=backrefs.end(); ++it) {
							(*it)->eraseFromParent();
						}

						break; // for now apply transform just once;
					}
				}
				//errs() << '\n';
			}

			for(BasicBlock::iterator I=BB.begin(), E=BB.end(); I!=E; ++I) {
				delete backref[&(*I)];
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
