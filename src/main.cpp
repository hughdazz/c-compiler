#include <iostream>
#include "parser/parse_def.h"
#include "code_gen/code_gen.h"
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>

Module *TheModule;
LLVMContext context;
std::ostream &operator<<(std::ostream &out, Value *v)
{
    assert(v != nullptr);
    std::string s;
    raw_string_ostream os(s);
    v->print(os);
    out << s;
}
int main()
{
    cJSON *tree;
    Value *code;

    parse(" int foo(int a,int b){b=sum(b*3,2);return b+a*9;} int sum(int a,int b){return a+b;}", &tree);
    std::cout << cJSON_Print(tree) << std::endl;
    TheModule = new Module("test", context);
    visitor<NodeType::Program>::code_gen(tree);
    TheModule->print(errs(), nullptr);

    //运行main函数
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();
    //使用MCJIT
    ExecutionEngine *EE = EngineBuilder(std::unique_ptr<Module>(TheModule)).create();
    //获取函数指针
    std::vector<GenericValue> args(2);
    args[0].IntVal = APInt(32, 1);
    args[1].IntVal = APInt(32, 2);

    int (*foo)(int, int) = (int (*)(int, int))EE->getFunctionAddress("foo");
    std::cout << foo(1, 2) << std::endl;
    return 0;
}