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

// 增加对局部变量的支持
static std::map<std::string, std::map<std::string, Value *>> NamedScopes;
static BasicBlock *ReturnBB = nullptr;
static Value *ErrorV(std::string msg)
{
    std::cout << msg << std::endl;
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
    // 不存在的节点
    ElemDec,
    // 不存在的节点
    ArrayDec,
    // 在语法树中不存在的节点，仅为了将函数定义的声明加入程序头部
    ExtProtoType,
    CompSt,
    DefList,
    Def,
    StmtList,
    Stmt,
    IfStmt,
    Exp,
    BinaryExr,
    FuncCall,
    Number,
    Variable,
    Array,
    REAL,
    ReturnStmt,
    WhileStmt,
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
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::ExtProtoType>
{
public:
    static Function *code_gen(cJSON *node);

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
class visitor<NodeType::FuncCall>
{
public:
    static Value *code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::CompSt>
{
public:
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::Variable>
{
public:
    static Value *code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::ReturnStmt>
{
public:
    static void code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::Stmt>
{
public:
    static void code_gen(cJSON *node);

private:
};
template <>
class visitor<NodeType::IfStmt>
{
public:
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::WhileStmt>
{
public:
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::Def>
{
public:
    static void code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::ElemDec>
{
public:
    static Value *code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::ArrayDec>
{
public:
    static Value *code_gen(cJSON *node);

private:
};

template <>
class visitor<NodeType::Array>
{
public:
    static Value *code_gen(cJSON *node);

private:
};