#include <iostream>
#include "parser/parse_def.h"
#include "AST/ast.h"
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include <fstream>
#include "code_gen/code_gen.h"
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

int main()
{
    cJSON *tree;
    // Value *code;

    //从test.c中读取c代码
    std::ifstream in("./test.array.c");
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    parse(src.c_str(), &tree);

    auto program = parse_raw_ast(tree);

    auto code_generator = CodeGen("test.lib.ll", (Program *)program.get());

    //运行main函数
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    //使用MCJIT
    ExecutionEngine *EE = EngineBuilder(code_generator.get_module()).create();
    //获取函数指针
    int (*main)() = (int (*)())EE->getFunctionAddress("main");
    main();
    return 0;
}