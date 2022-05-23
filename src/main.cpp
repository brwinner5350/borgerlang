// main.cpp
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

int main() {
    llvm::LLVMContext context;

    std::unique_ptr<llvm::Module> mod;
    mod = std::make_unique<llvm::Module>("Borgerlang module", context);

    // Build the IR for this block
    llvm::IRBuilder<> builder(context);

    // Main returns void
    llvm::FunctionType *mainReturnType = 
        llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);

    // The main function
    llvm::Function *mainFunction =
        llvm::Function::Create(mainReturnType, llvm::Function::ExternalLinkage, "borger_entry", mod.get()); // TODO: change this to main later on

    // Create the function's body
    llvm::BasicBlock *body = llvm::BasicBlock::Create(context, "body", mainFunction);
    builder.SetInsertPoint(body);

    builder.CreateRetVoid();
    mod->print(llvm::outs(), nullptr);

    return 0;
}
