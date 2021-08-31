#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <llvm/Support/raw_ostream.h>
using namespace llvm;



namespace {
  struct Malloc_to_secure_mallocPass : public FunctionPass {
    static char ID;
    Malloc_to_secure_mallocPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
  	
	for (auto& B : F) {
  		for (auto& I : B) {		
  			if(CallInst* call_inst = dyn_cast<CallInst>(&I)) {  // on vérifie si l'instruction est de type appel de fonction
  		
                		Function* fn = call_inst->getCalledFunction();   //on récupère la fonction appelée
                		StringRef fn_name = fn->getName();              // on récupère le nom de ladite fonction
                		if (fn_name=="malloc"){                       // si c'est un appel malloc
                			
                			// on affiche le nom de la fonction et la
                			errs() << "function name : " << fn_name <<"\n"; 
                			errs() << "size of allocation : " << *(call_inst->getOperand(0)) <<"\n";      
                		}
                		
               		/* for(auto arg = fn->arg_begin(); arg != fn->arg_end(); ++arg) {
  				if(auto* ci = dyn_cast<ConstantInt>(arg))
    				errs() << ci->getValue() << "\n";
  				errs() << *arg << "\n";
				}*/
			
				// on retourne faux car on a pas encore modifié notre programme
                		return false;
                	}
    	
  		}
	}	
    }
 };
}

char Malloc_to_secure_mallocPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerMalloc_to_secure_mallocPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new Malloc_to_secure_mallocPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerMalloc_to_secure_mallocPass);
