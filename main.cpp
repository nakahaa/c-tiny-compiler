#include <iostream>
#include <fstream>
#include "ast.h"
#include "codegen.h"
#include <stdio.h>
#include "objgen.h"

extern shared_ptr<NBlock> programBlock;
extern int yyparse();

const int MAIN_COMPILE =  0;
const int MAIN_DUMP_TREE = 1;
const int MAIN_SYNTAX_CHECK = 2;

int parse_args(int argc, char* argv[])
{
    int i;

    for (i = 0; i < argc; ++i)
    {
        if (!strcmp(argv[i], "--compile"))
            return MAIN_COMPILE;
        else if (!strcmp(argv[i], "--dump-tree"))
            return MAIN_DUMP_TREE;
        else if (!strcmp(argv[i], "--syntax-check"))
            return MAIN_SYNTAX_CHECK;
    }
    return -1;
}

void print_usage_message()
{
    const char* message =
        "ToyC Compiler\n"
        "--compile & --dump-tree & --syntax-check";

    fputs(message, stderr);
}

int main(int argc, char* argv[]) {
    yyparse();
    int iarg;
    iarg = parse_args(argc, argv);

    if ( iarg == MAIN_COMPILE ) {
        cout<< "compiling " <<endl;
        programBlock->print("--");
        auto root = programBlock->json_pretty();
        CodeGenContext context;
        context.generateCode(*programBlock);
        ObjGen(context);
    } else if ( iarg == MAIN_DUMP_TREE ) {
        auto root = programBlock->json_pretty();
        string jsonFile = "tree.json";
        std::ofstream astJson(jsonFile);
        if( astJson.is_open() ){
            astJson << root;
            astJson.close();
            cout << "write tree into: " << jsonFile << endl;
        }
    } else if (iarg == MAIN_SYNTAX_CHECK ) {
        programBlock->print("--");
    } else {

        print_usage_message();
    }

    return 0;
}