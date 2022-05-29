#include <stack>
#include <typeinfo>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitstream/BitstreamReader.h>
#include <llvm/Bitstream/BitstreamWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

class NBlock;

static llvm::LLVMContext GlobalContext;

class CodeGenBlock
{
public:
    llvm::BasicBlock *block;
    llvm::Value *retval;
    std::map<std::string, llvm::Value*> locals;
};

class CodeGenContext
{
    std::stack<CodeGenBlock*> blocks;
    llvm::Function *entry;
public:
    llvm::Module *module;

    CodeGenContext()
    {
        module = new llvm::Module("Borgerlang module", GlobalContext);
    }

    void generateCode(NBlock &root);
    llvm::GenericValue runCode();

    std::map<std::string, llvm::Value*>& locals() { return blocks.top()->locals; }
    
    llvm::BasicBlock *currentBlock() { return blocks.top()->block; }
    
    void pushBlock(llvm::BasicBlock *block)
    {
        blocks.push(new CodeGenBlock());
        blocks.top()->retval = NULL;
        blocks.top()->block = block;
    }
    void popBlock()
    {
        CodeGenBlock *top = blocks.top();
        blocks.pop();
        delete top;
    }
    void setCurrentRetval(llvm::Value *val) { blocks.top()->retval = val; }
    llvm::Value *getCurrentRetval() { return blocks.top()->retval; }
};