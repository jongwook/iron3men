#define DEBUG_TYPE "sb-opt-loop"
#include "llvm/Module.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Constants.h"
#include "llvm/DerivedTypes.h"
//#include "llvm/IntrinsicInst.h"
#include "llvm/Instructions.h"
//#include "llvm/InstrType.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/AliasSetTracker.h"
#include "llvm/Analysis/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Support/CFG.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Analysis/ProfileInfo.h"
#include "llvm/Analysis/ProfileInfoLoader.h"
#include <stdio.h>
#include <algorithm>
#include <list>
#include <map>
#include <vector>

using namespace llvm;

namespace {

  struct SBOptLoopPass : public LoopPass {
//    ProfileInfo *pInfo;
    static bool header;
    static char ID; // Pass identification, replacement for typeid
    std::list<BasicBlock* > BBs;
    std::list<BasicBlock* > DupBlocks;
    std::list<BasicBlock* > SB;
    std::list<Instruction* > ClonedPhis;
    std::list<BasicBlock* >::iterator it;
    std::map<BasicBlock*, BasicBlock* > BtoDupB;
    std::map<Instruction*, Instruction* > PhitoClonedPhi;
    std::map<Instruction*, Instruction* > PhitoSelectI;
    std::map<Value*, Value* > SelectItoPhi;
    std::map<Value*, Value* > ItoClonedI;
    std::map<Value*, Value* > ValToSelectI;
    std::map<Value*, Value* > PhiToVal;
    
    ProfileInfo *PI;
    DominatorTree *DT;
    LoopInfo *LI;
    bool isDubBlock;
    
    SBOptLoopPass() : LoopPass(ID) {}
     
    virtual bool runOnLoop(Loop *L, LPPassManager &LPM) {
    	
    	errs() << "runOnLoop\n";
    	DT = &getAnalysis<DominatorTree>();
    	LI = &getAnalysis<LoopInfo>();
    	PI = &getAnalysis<ProfileInfo>();
    	BBs.clear();
    	isDubBlock = false;
    	std::vector<Loop* > sub_loop = L->getSubLoops();
    	
    	// inner most loop
    	if ((L->end() - L->begin()) == 0)
    	{
    		DomTreeNode *root = DT->getRootNode();
    		BasicBlock* header = L->getHeader();
				BasicBlock* preheader = L->getLoopPreheader(); 	
    		//DomTreeNodeBase<BasicBlock *>::iterator it;
    		printBlocks(root);
 				getBlocks(L, root);
 				updatePhiOperands(root); 
 				
 				//errs() << BBs.size() << " BBBBBB\n";
 				bool added = true;
 				SB.push_back(BBs.front());
 				//for (it=BBs.begin();it!=BBs.end();++it)
 				//{
 				
 				
 				// Find a group of basicblock that can form superblock
 				while (added)
 				{
 					added = false;
 					TerminatorInst *ti;
 					//errs() << SB.size() << " SB\n";
					BasicBlock *b = SB.back();
					ti = b->getTerminator();
					int numSucc = ti->getNumSuccessors();
					//std::list<BasicBlock* > succ;
					BasicBlock *maxBB;
					double maxWeight = 0.0;
					double sum = 0.0;
					for (int i=0;i<numSucc;i++)
					{
						BasicBlock* bb = ti->getSuccessor(i);
						ProfileInfo::Edge e = ProfileInfo::getEdge(b, bb);
						double w = PI->getEdgeWeight(e);
						sum += w;
						if (maxWeight < w)
						{
							maxWeight = w;
							maxBB = bb;
						}
					}
//					errs() << maxBB << "\n" << maxWeight << " " << sum << "\n";
					if (maxWeight/sum > 0.6 && numSucc > 0)
					{ 
						bool contain = false;
						for (it=SB.begin();it!=SB.end();it++)
						{
							BasicBlock *tempB = *it;
							if (tempB == maxBB) contain = true;
						}
						if (!contain) 
						{
							SB.push_back(maxBB);
							added = true;
						}
					}
 				} // end while
// 				errs() << SB.size() << " SB SIZE\n";
 				getDupBlocks(L, root);
 				
 				added = true;
 				// Tail duplication
 				while (added)
 				{
					added = false;
					BasicBlock *b = DupBlocks.back();
					
					TerminatorInst *ti = b->getTerminator();
					int numSucc = ti->getNumSuccessors();
					
					for (unsigned int i = 0; i < numSucc; i += 1)
					{
						BasicBlock *bb = ti->getSuccessor(i);
						
						if (bb != L->getHeader())
						{
							DupBlocks.push_back(bb);
							added = true;
						}
					} 				
 				}
 				std::vector<BasicBlock *> DupedBBs;
 				BasicBlock* DupHeader;
 				if (!DupBlocks.empty()) 
 				{
 					DupHeader = DupBlocks.front();
 					DupBlocks.pop_front();
 					DupedBBs.push_back(DupHeader);
 				}
 				ValueToValueMapTy map;
 				for (it=DupBlocks.begin();it!=DupBlocks.end();++it)
 				{
 					BasicBlock *b = *it;
 					BasicBlock *cloneBB = CloneBasicBlock(*it, map, "_new");
 					DupedBBs.push_back(cloneBB);
 					BtoDupB[*it] = cloneBB;
 					Function* f = (*it)->getParent();
 					f->getBasicBlockList().push_back(cloneBB);
// 					DT->addNewBlock(cloneBB, cloneBB->getSinglePredecessor());
 					
 					BasicBlock::iterator bit;
 					BasicBlock::iterator bit2;
 					
 					for (bit=b->begin(), bit2=cloneBB->begin(); bit!=b->end(); ++bit, ++bit2)
 					{
 						Instruction& inst1 = *bit;
 						Instruction& inst2 = *bit2;
 						
 						//Instruction* i1 = &inst1;
 						
 						ItoClonedI[&inst1] = &inst2;
 					}
// 					errs() << cloneBB->getName() << "\n";
 				}
				
				
				// Update terminator instructions for duplicated blocks
				// NOTE: NOT COMPLETE YET
				for (int i=0;i<DupedBBs.size();i++)
				{
					BasicBlock* cur = DupedBBs.at(i);										
					if (i<DupedBBs.size()-1)
					{
						BasicBlock* succ = DupedBBs.at(i+1);
						
						TerminatorInst* ti = cur->getTerminator();
						if (BranchInst* bi = dyn_cast<BranchInst>(ti))
						{
							if (bi->isConditional())
							{
								Value* cond = bi->getCondition();
								BasicBlock* b1 = bi->getSuccessor(0);
								BasicBlock* b2 = bi->getSuccessor(1);
								
								if (BtoDupB.count(b1)>0)
								{
									b1 = BtoDupB[b1];
								}
								if (BtoDupB.count(b2)>0)
								{
									b2 = BtoDupB[b2];
								}
								cur->getInstList().pop_back();
								BranchInst* new_bi = BranchInst::Create(b1, b2, cond, cur);
							}
							if (bi->isUnconditional())
							{
								cur->getInstList().pop_back();
								BranchInst* new_bi = BranchInst::Create(succ, cur);
							}
						}
						else
						{
//							errs() << "!!!!!!!!!!!!!!!\n";
							TerminatorInst* new_ti = dyn_cast<TerminatorInst>(ti->clone());
							new_ti->setSuccessor(0, succ);
							cur->getInstList().pop_back();
							cur->getInstList().push_back(new_ti);
						}
//						BranchInst* new_bi = BranchInst::Create()
					}
					errs() << *cur << "\n";
					
					// Handling PHI Nodes
					if (i>0)
					{
						BasicBlock::iterator inst_it;
						std::vector<BasicBlock *> BBtoRemove;
						for (inst_it = cur->begin(); inst_it != cur->end(); ++inst_it)
						{
							Instruction &i = *inst_it;
							
							if (PHINode* phi =  dyn_cast<PHINode>(&i))
							{
								std::vector<BasicBlock *> incBBs;
								unsigned int count=0;
								for (unsigned int i = 0; i < phi->getNumIncomingValues(); i += 1)
								{
	//								incBBs.push_back(phi->getIncomingBlock(i));
									BasicBlock* incBB = phi->getIncomingBlock(i);
									if (BtoDupB.count(incBB)>0)
									{
										incBB = BtoDupB[incBB];
										phi->setIncomingBlock(i, incBB);
										count++;
									}
									else
									{
										BBtoRemove.push_back(incBB);
//										errs() << "to remove: " << incBB << "\n";
										//cur->removePredecessor(incBB);
									}
								}
							
								if (count==0) 
								{
	//								cur->getInstList().pop_front();
	//								phi->eraseFromParent();
	//								--inst_it;
								}
							}
						}
					
						for (int i=0;i<BBtoRemove.size();i++)
						{
							BasicBlock* b = BBtoRemove.at(i);
							cur->removePredecessor(b);
						}
					}
					errs() << *cur << "\n";
					errs() << "------------\n";
					for (it=SB.begin();it!=SB.end();it++)
					{
						errs() << *it << "\n";
					}
				}
				// Clearing PHI nodes from non-header SB-blocks			
				BasicBlock::iterator inst_it;
				TerminatorInst* term = header->getTerminator();
				//header->getInstList().pop_back();
				
				
				for (it=SB.begin();it!=SB.end();++it)
				{
					BasicBlock* cur = *it;
					Module* M = (preheader->getParent())->getParent();
					// non-header
					if (cur != header)
					{
						
						std::vector<BasicBlock *> BBtoRemove;
						for (inst_it = cur->begin(); inst_it != cur->end(); ++inst_it)
						{
							Instruction &i = *inst_it;
						
							if (PHINode* phi =  dyn_cast<PHINode>(&i))
							{
								Instruction* cloned_inst = phi->clone();
								PHINode* cloned_phi =  dyn_cast<PHINode>(cloned_inst);
								
								int num_val = phi->getNumIncomingValues();
								
//								AllocaInst* flagAlloc = new AllocaInst(Type::getInt1Ty(M->getContext()), 0,"flag",preheader->getTerminator());
//								StoreInst* flagStore = new StoreInst(ConstantInt::get(IntegerType::get(M->getContext(), 1), 1, false), flagAlloc, preheader->getTerminator());
//								StoreInst* flagStore2 = new StoreInst(ConstantInt::get(IntegerType::get(M->getContext(), 1), 1, false), flagAlloc, SB.back()->getTerminator());
//								StoreInst* flagStore3 = new StoreInst(ConstantInt::get(IntegerType::get(M->getContext(), 1), 1, false), flagAlloc, BtoDupB[SB.back()]->getTerminator());
//								LoadInst* flagLoad = new LoadInst(flagAlloc, "flag_load", header->getTerminator());
								
								std::vector<Value *> vlist;
								for (unsigned int i = 0; i < num_val; i += 1)
								{
									BasicBlock* incB = cloned_phi->getIncomingBlock(i);
									Value *v = phi->getIncomingValue(i);
									vlist.push_back(v);
									std::list<BasicBlock* >::iterator bit;
									bool inSB = false;
									for (bit=SB.begin();bit!=SB.end();++bit)
									{
										BasicBlock* sb_block = *bit;
										if (sb_block == incB) inSB = true;
									}
									if (inSB) 
									{
										cloned_phi->setIncomingBlock(i, SB.back());
										cloned_phi->addIncoming(ConstantInt::get(IntegerType::get(M->getContext(), 32), 1, false), preheader);
									}
									else cloned_phi->setIncomingBlock(i,BtoDupB[SB.back()]);
								}								
								
								Value& v1 = *(vlist[0]);
								Value& v2 = *(vlist[1]);
//								SelectInst* selectInst = SelectInst::Create(dyn_cast<Value>(flagLoad), &v1, dyn_cast<Value>(cloned_phi), "slt_flag", header->getTerminator());
//								ValToSelectI[&v1] = dyn_cast<Value>(selectInst);
								PhiToVal[phi] = &v1;
//								const Type* t = Type::getInt32Ty(M->getContext());
//								ConstantInt* flag_true = ConstantInt::get(IntegerType::get(M->getContext(), 32), 1, false);
//								Value* val = new Value(t, 100);
//								cloned_phi->addIncoming(ConstantInt::get(IntegerType::get(M->getContext(), 32), 0, true), preheader);
								

//								cloned_phi->addIncoming(cloned_phi, preheader);
								
								
//				StoreInst* flagStore = new StoreInst(flag_false, flagAlloc, entryBlock.getTerminator());
//								cloned_phi->insertBefore(term);
								header->getInstList().push_front(cloned_phi);
								
								PhitoClonedPhi[phi] = cloned_inst;
//								PhitoSelectI[phi] = selectInst;
//								SelectItoPhi[dyn_cast<Instruction>(selectInst)] = dyn_cast<Instruction>(phi);
//								PhitoClonedPhi[phi] = selectInst;
//								ClonedPhis.push_back(phi);
								ClonedPhis.push_back(phi);
								
								std::vector<BasicBlock *> incBBs;
								unsigned int count=0;
								for (unsigned int i = 0; i < phi->getNumIncomingValues(); i += 1)
								{
									BasicBlock* incBB = phi->getIncomingBlock(i);
									if (BtoDupB.count(incBB)>0)
									{
										incBB = BtoDupB[incBB];
										phi->setIncomingBlock(i, incBB);
										count++;
									}
									else
									{
										BBtoRemove.push_back(incBB);
									}
								}
							}
						}
						
						updatePhiOperands(root);
						
						for (int i=0;i<DupedBBs.size();i++)
						{
							BasicBlock* cur = DupedBBs.at(i);
							//updatePhiOperands(cur);
						}
						
						for (int i=0;i<BBtoRemove.size();i++)
						{
							BasicBlock* b = BBtoRemove.at(i);
							cur->removePredecessor(b);
						}
					}
				} // end for
				
//				header->getInstList().push_back(term);
				
				
				for (inst_it=header->begin();inst_it!=header->end();++inst_it)
				{
					Instruction &i = *inst_it;
						
					if (PHINode* phi =  dyn_cast<PHINode>(&i))
					{
						int num_val = phi->getNumIncomingValues();
						
						for (unsigned int i = 0; i < num_val; i += 1)
						{
							BasicBlock* b = phi->getIncomingBlock(i);
							
							if (BtoDupB.count(b)>0)
							{
								Value* v = phi->getIncomingValue(i);
								if (ItoClonedI.count(v) > 0)
								{
//									errs() << "VVV:\n" << *v;
									if (phi->getBasicBlockIndex(BtoDupB[b]) == -1)	
										phi->addIncoming(ItoClonedI[v], BtoDupB[b]);	
								}
//								else if(SelectItoPhi.count(v)>0)
//								{
//									if (phi->getBasicBlockIndex(BtoDupB[b]) == -1)	
//										phi->addIncoming(dyn_cast<Value>(SelectItoPhi[v]), BtoDupB[b]);	
//								}
								else
								{
									if (phi->getBasicBlockIndex(BtoDupB[b]) == -1)	
										phi->addIncoming(v, BtoDupB[b]);	
								}
							}
						}
					}
				}
//				updatePhiOperands(root);		
				
				for (int i=0;i<DupedBBs.size();i++)
				{
					BasicBlock* cur = DupedBBs.at(i);
					for (inst_it=cur->begin();inst_it!=cur->end();++inst_it)
					{
						Instruction &inst = *inst_it;
						unsigned int num_op = inst.getNumOperands();
						
						for (unsigned int i = 0; i < num_op; i += 1)
						{
							if (ItoClonedI.count(inst.getOperand(i)) > 0)
							{
								inst.setOperand(i,ItoClonedI[inst.getOperand(i)]);
							}
						}
					}
				}
				
				errs() << "Header: \n" << *header;
				printBlocks(root);
				for (int i=0;i<DupedBBs.size();i++)
				{
					BasicBlock* cur = DupedBBs.at(i);
					errs() << *cur << "\n";
				}
//				std::list<Instruction *>::iterator inst_it;
//				for (inst_it = ClonedPhis.begin();inst_it!=ClonedPhis.end();++inst_it)
//				{
//					PHINode* i = dyn_cast<PHINode>(*inst_it);
//					errs() << *i;
//				}
			////////////////// END Superblock Formulation ////////////////////////////
      
      prepareOptimization(L);
				
      } // end if
      
      return true;
    }
    
    void prepareOptimization(Loop* L)
    {
    	BasicBlock *hb = SB.front();
    	std::vector<Instruction *> vec;
    	for (it=SB.begin();it!=SB.end();it++)
    	{
    		if (*it != L->getHeader())
    		{
    			BasicBlock* b = *it;
    			
    			BasicBlock::iterator bit;
    			
    			int count = 0;
    			for (bit=b->begin();bit!=b->end();++bit)
    			{
    				Instruction& inst = *bit;
    				if (count < 8) 
  					{
  						vec.push_back(&inst);
  						count++;
//    					inst.moveBefore(hb->getTerminator());
//    					count = 1;
//    					break;
    				}
//    				if (isa<ICmpInst>(inst) || isa<BranchInst>(inst) || isa<CmpInst>(inst))
//    				{
//    				}
//    				else
//    				{
//    					inst.moveBefore(L->getHeader()->getTerminator());
//    				}
    			}
    		}
    	}
    	
    	for (int i=0;i<vec.size();i++)
    	{
    		Instruction* inst = vec.at(i);
    		inst->moveBefore(hb->getTerminator());
    	}
    	
    	for (it=SB.begin();it!=SB.end();it++)
    	{
    		BasicBlock* b = *it;
    		errs() << *b << "\n";
			}
    }
    
    void getDupBlocks(Loop* L, DomTreeNode *N)
		{
			BasicBlock* BB = N->getBlock();
			errs() << "DubBlock Called: " << *BB;
			//BBs.push_back(BB);
			if (!isDubBlock && L->getLoopPreheader() != BB)
			{
				bool inSB = false;
				errs() << "SB SIZE!!!:" << SB.size();
				for (it = SB.begin(); it != SB.end(); ++it)
				{
					BasicBlock *tempB = *it;
					errs() << "tempB: " << tempB << " BB: " << BB << "\n";
					if (tempB == BB)
					{
						inSB = true;
						errs() << "inSB false\n";
					} 
				}
			
				if (!inSB)
				{
					TerminatorInst *ti;
					ti = BB->getTerminator();
					int numSucc = ti->getNumSuccessors();
					for (int i=0;i<numSucc;i++)
					{
						BasicBlock* b = ti->getSuccessor(i);
						for (it = SB.begin(); it != SB.end(); ++it)
						{
							BasicBlock *tempB = *it;
							if (tempB == b) 
							{
								isDubBlock = true;
								DupBlocks.push_back(BB);
							}
						}
					}
				}
			}
			
			const std::vector<DomTreeNode*> &Children = N->getChildren();
			for (unsigned i = 0, e = Children.size(); i != e; ++i)
			getDupBlocks(L, Children[i]);
		}
		 
    void getBlocks(Loop* L, DomTreeNode *N)
		{
			BasicBlock* BB = N->getBlock();
			if (!(L->getLoopPreheader() == BB))
			{
//				errs() << "Preheader:::\n" << *BB;
				BBs.push_back(BB);
			}
			
			const std::vector<DomTreeNode*> &Children = N->getChildren();
			for (unsigned i = 0, e = Children.size(); i != e; ++i)
			getBlocks(L, Children[i]);
		} 
     
    void printBlocks(DomTreeNode *N)
		{
			BasicBlock* BB = N->getBlock();
			errs() << *BB;
			//BBs.push_back(BB);

			const std::vector<DomTreeNode*> &Children = N->getChildren();
			for (unsigned i = 0, e = Children.size(); i != e; ++i)
			printBlocks(Children[i]);
		}
		
		void updatePhiOperands(DomTreeNode *N)
		{
			BasicBlock* BB = N->getBlock();
			BasicBlock::iterator inst_it;
			std::list<Instruction *>::iterator iit;
			
			for (inst_it=BB->begin();inst_it!=BB->end();++inst_it)
			{
				Instruction &inst = *inst_it;
				
				int num_op = inst.getNumOperands();
				
				for (int i=0;i<num_op;i++)
				{
					for (iit=ClonedPhis.begin();iit!=ClonedPhis.end();++iit)
					{
						PHINode* phi = dyn_cast<PHINode>(*iit);
						if (inst.getOperand(i) == phi)
						{
//							errs() << "!!!!!!!!!!!\n";
//							errs() << inst << " " << *phi << "\n";
//							if (PHINode* phi2 = dyn_cast<PHINode>(&inst))
//							{
//								phi2->setIncomingValue(1, PhitoSelectI[phi]);
//							}
//							else inst.setOperand(i, PhitoSelectI[phi]);
//							inst.setOperand(i, PhitoSelectI[phi]);
							inst.setOperand(i, PhiToVal[phi]);	
							if (PHINode* phi2 = dyn_cast<PHINode>(&inst))
							{
								int num_inc = phi2->getNumIncomingValues();
								for (int j=0;j<num_inc;j++)
								{
									BasicBlock *bb = phi2->getIncomingBlock(j);
	//								errs() << "BBBBBBBBBb\n";
	//								errs() << BtoDupB.count(bb);
									if (BtoDupB.count(bb) > 0)
									phi2->addIncoming(phi, BtoDupB[bb]);
								}
							}
						}
						if (ValToSelectI.count(inst.getOperand(i)))
						{
							if (SelectInst* SIS = dyn_cast<SelectInst>(&inst))
							{
							}
							//else inst.setOperand(i, ValToSelectI[inst.getOperand(i)]);
						}
					}
				}
			}			
			
			const std::vector<DomTreeNode*> &Children = N->getChildren();
			for (unsigned i = 0, e = Children.size(); i != e; ++i)
			updatePhiOperands(Children[i]);
		}
		
		void updatePhiOperands(BasicBlock *BB)
		{
			BasicBlock::iterator inst_it;
			std::list<Instruction *>::iterator iit;
			
			for (inst_it=BB->begin();inst_it!=BB->end();++inst_it)
			{
				Instruction &inst = *inst_it;
				
				int num_op = inst.getNumOperands();
				
				for (int i=0;i<num_op;i++)
				{
					for (iit=ClonedPhis.begin();iit!=ClonedPhis.end();++iit)
					{
						PHINode* phi = dyn_cast<PHINode>(*iit);
						if (inst.getOperand(i) == phi)
						{
							inst.setOperand(i, PhitoSelectI[phi]);
						}
					}
				}
			}			
		}
     
    virtual void getAnalysisUsage(AnalysisUsage &AU) const {
      AU.setPreservesCFG(); 
    //  AU.addRequired<ProfileInfo>();
    	AU.addRequired<LoopInfo>(); 
		  AU.addRequired<DominatorTree>();
		  /* 
		  AU.addRequired<DominanceFrontier>(); 
		  AU.addRequired<AliasAnalysis>(); 
		  AU.addPreserved<ScalarEvolution>(); 
		  AU.addPreserved<DominanceFrontier>();
		  */ 
		  //AU.addPreservedID(LoopSimplifyID); 
		  //AU.addRequired<LAMPLoadProfile>(); 
		  AU.addRequired<ProfileInfo>();
    }
  };
  
  //Pass *llvm::createSBOptLoopPass() { return new SBOptLoopPass(); }
}

char SBOptLoopPass::ID = 4;
bool SBOptLoopPass::header = false;
INITIALIZE_PASS(SBOptLoopPass, "sb-opt-loop",
                "Superblock Optimization Loop Pass", false, false);
                
                
//static RegisterPass<PeepholeFunctionPass> ds ("peephole_opt_func_pass", "Peephole Optimizer Function Pass");

