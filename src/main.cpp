// main.cpp
#include <iostream>
#include <stdio.h>
#include "codegen.h"
#include "node.h"

using namespace llvm;

extern NBlock *programBlock;
extern int yyparse();
extern FILE* yyin;

void createCorefuncs(CodeGenContext& context);

int main() 
{
    FILE* fp = fopen("./code.bgl", "r");
    if (fp) // the last thing we want is to parse a file that doesn't exist
        yyin = fp;
    else
        std::cout << "code.bgl not found, enter code in stdin:" << std::endl;    
    yyparse();
    std::cout << programBlock << std::endl;

    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    CodeGenContext context;
    createCorefuncs(context);
    context.generateCode(*programBlock);
    context.runCode();

    return 0;
}
