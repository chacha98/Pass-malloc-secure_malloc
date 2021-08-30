#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;


namespace {
  struct Malloc_to_secure_mallocPass : public FunctionPass {
    static char ID;
    Malloc_to_secure_mallocPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      //errs() << "I saw a function called " << F.getName() << "!\n";
      /*errs() << "Function body:\n" << F << "\n";
      for (auto& B : F) {
  	errs() << "Basic block:\n" << B << "\n";
  	for (auto& I : B) {
    		errs() << "Instruction: " << I << "\n";
  	}
	}*/

	for (auto& B : F) {
  		for (auto& I : B) {
	
  		if(CallInst* call_inst = dyn_cast<CallInst>(&I)) {
                Function* fn = call_inst->getCalledFunction();
                StringRef fn_name = fn->getName();
                //errs() << fn_name << " : " << fn_name->arg_begin()<<"\n";
                errs() << fn_name << " : " << call_inst->getArgOperand(0) << "\n";
                for(auto arg = fn->arg_begin(); arg != fn->arg_end(); ++arg) {
  		if(auto* ci = dyn_cast<ConstantInt>(arg))
    		errs() << ci->getValue() << "\n";
  		errs() << *arg << "\n";
		}
                return false;
                }
    			/*if (auto* op = dyn_cast<BinaryOperator>(&I)) {
      		// Insert at the point where the instruction `op` appears.
      			IRBuilder<> builder(op);

      			// Make a multiply with the same operands as `op`.
     			 Value* lhs = op->getOperand(0);
      			 Value* rhs = op->getOperand(1);
      			 Value* mul = builder.CreateMul(lhs, rhs);

      			// Everywhere the old instruction was used as an operand, use our
      			// new multiply instruction instead.
      			for (auto& U : op->uses()) {
        			User* user = U.getUser();  // A User is anything with operands.
        			user->setOperand(U.getOperandNo(), mul);
      			}

     			 // We modified the code.
     			 return true;
   			 }*/
  		}
	}	
}
};
}

char Malloc_to_secure_mallocPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new Malloc_to_secure_mallocPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
