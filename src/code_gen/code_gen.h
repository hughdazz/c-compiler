#pragma once
#include "AST/ast.h"
#include "parser/parse_def.h"
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/TargetSelect.h>
#include "code_gen/code_gen.h"
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
using namespace llvm;
static LLVMContext context;

class CodeGen
{
private:
    Program *program;
    std::unique_ptr<Module> TheModule;
    std::unique_ptr<IRBuilder<>> Builder;
    std::map<std::string, std::map<std::string, Value *>> NamedScopes;
    BasicBlock *now_return = nullptr;
    Function *now_F = nullptr;
    int has_error = 0;
    void gen_ExtProtoType(FunDec *fun_dec);
    Type *gen_VarDec_Type(VarDec *var_dec, Type *var_type);
    Type *get_type(SpecType spec_type);

    Value *gen_Exp(Exp *exp);
    Value *get_lvalue(std::string scope_name, std::string var_name);

public:
    CodeGen(Program *program);
    CodeGen(std::string lib_path, Program *program);
    template <class Node>
    void code_gen(Node *node);
    void put_error(std::string msg)
    {
        std::cout << msg << std::endl;
        has_error = 1;
    }
    std::unique_ptr<Module> get_module()
    {
        return std::move(TheModule);
    }
};