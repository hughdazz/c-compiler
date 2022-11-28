#include <iostream>
#include "parser/parse_def.h"
#include "code_gen/code_gen.h"
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include <fstream>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
Module *TheModule;
LLVMContext context;

int main()
{
    cJSON *tree;
    Value *code;

    //从test.c中读取c代码
    std::ifstream in("./test.array.c");
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();
    std::cout << src << std::endl;

    parse(src.c_str(), &tree);
    std::cout << cJSON_Print(tree) << std::endl;

    SMDiagnostic err;
    TheModule = parseIRFile("test.lib.ll", err, context).release();
    TheModule->setSourceFileName("test");
    visitor<NodeType::Program>::code_gen(tree);
    TheModule->print(errs(), nullptr);

    //运行main函数
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    //使用MCJIT
    ExecutionEngine *EE = EngineBuilder(std::unique_ptr<Module>(TheModule)).create();
    //获取函数指针
    int (*main)() = (int (*)())EE->getFunctionAddress("main");
    main();
    return 0;
}