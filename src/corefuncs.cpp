#include <iostream>
#include "codegen.h"
#include "node.h"

/**
 * @brief This function creates the LLVM equivalent of printf.
 * 
 * @param context 
 * @return llvm::Function* 
 */
llvm::Function *createPrintfFunction(CodeGenContext& context)
{
    std::vector<llvm::Type*> argTypes;
    argTypes.push_back(llvm::Type::getInt8PtrTy(GlobalContext)); // char*

    llvm::FunctionType *funcType = llvm::FunctionType::get(llvm::Type::getInt32Ty(GlobalContext), argTypes, true);

    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, llvm::Twine("printf"), context.module);

    func->setCallingConv(llvm::CallingConv::C);

    return func;
}

/**
 * @brief Create the core Borgerlang functions.
 * 
 * @param context 
 */
void createCorefuncs(CodeGenContext& context)
{
    createPrintfFunction(context);
}