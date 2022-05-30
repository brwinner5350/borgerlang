// main.cpp
#include <iostream>
#include <stdio.h>
#include "codegen.h"
#include "node.h"

using namespace llvm;

extern NBlock *programBlock;
extern FILE* yyin;
extern int yydebug;
extern int yyparse();

extern int linenum;

void createCorefuncs(CodeGenContext& context);

void yyerror(const char *msg)
{
    printf("Error at line %d: %s.\n", linenum, msg);
}

int main()
{
    yydebug = 1;
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
