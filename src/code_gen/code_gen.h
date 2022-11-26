#pragma once
#include <iostream>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include "parser/parse_def.h"

using namespace llvm;
extern LLVMContext context;
extern Module *TheModule;
static IRBuilder<> Builder(context);
static std::map<std::string, Value *> NamedValues;
// class GenError : public ErrorInfo<GenError>
// {
// public:
//     const char ID = '1';
//     GenError(std::string msg) : msg(msg) {}
//     void log(raw_ostream &OS) const override
//     {
//         OS << msg;
//     }
//     std::error_code convertToErrorCode() const override
//     {
//         return std::error_code();
//     }
//     std::string msg;
// };
static Value *ErrorV(std::string msg)
{
    // GenError(msg).log(errs());
    return nullptr;
}
enum class NodeType
{
    Program,
    ExtDefList,
    ExtDecList,
    ExtDef,
    Specifier,
    FunDec,
    CompSt,
    DefList,
    StmtList,
    Stmt,
    Exp,
    BinaryExr,
    FunCall,
    Number,
    ID,
    REAL,
    ReturnStmt,
};

template <NodeType type>
class visitor
{
public:
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::Program>
{
public:
    static Value *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::ExtDef>
{
public:
    static void code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::FunDec>
{
public:
    static Function *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::Number>
{
public:
    static Value *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::ID>
{
public:
    static Value *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::BinaryExr>
{
public:
    static Value *code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::Exp>
{
public:
    static Value *code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::FunCall>
{
public:
    static Value *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::CompSt>
{
public:
    static Value *code_gen(cJSON *node);

private:
};