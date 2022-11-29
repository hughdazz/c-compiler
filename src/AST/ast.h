#pragma once
#include "../../deps/cjson/cJSON.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

enum class NodeType
{
    Program,
    ExtDef,
    Stmt,
    VarDec,
    Exp,
    Def,
    Dec,
    ParamDec,
};
enum class NodeSubType
{
    FunDec,
    CompSt,
    ElemDec,
    ArrayDec,

    ReturnStmt,
    IfStmt,
    WhileStmt,
    ExpStmt,
    BinaryExp,
    FuncCall,
    Number,
    Variable,

    BasicExp,
    ArrayExp,

    ExtDecList,
};
enum class OpType
{
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    PLUS,
    MINUS,
    STAR,
    DIV,
    AND,
    OR,
    NOT,
    ASSIGNOP,
};
enum class SpecType
{
    Int,
    Float,
    Void,
    Name,
};
class Node
{
public:
    NodeType type;
};
class Dec : public Node
{
public:
    std::unique_ptr<Node> var_dec;
    std::unique_ptr<Node> exp;
    SpecType spec_type;
};

class Def : public Node
{
public:
    SpecType spec_type;
    std::vector<std::unique_ptr<Node>> dec_list;
};

class Stmt : public Node
{
public:
    NodeSubType sub_type;
};

class ExtDef : public Node
{
public:
    NodeSubType sub_type;
};
class Exp : public Node
{
public:
    NodeSubType sub_type;
};

class BasicExp : public Exp
{
public:
    SpecType spec_type;
    int int_val;
    float float_val;
    std::string name_val;
};
class BinaryExp : public Exp
{
public:
    OpType op;
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
};
class AssignExp : public Exp
{
public:
    std::unique_ptr<Node> lhs;
    std::unique_ptr<Node> rhs;
};
class FuncCall : public Exp
{
public:
    std::string name;
    std::vector<std::unique_ptr<Node>> args;
};
class ArrayExp : public Exp
{
public:
    std::unique_ptr<Node> array;
    std::unique_ptr<Node> index;
};

class ExtDecList : public ExtDef
{
public:
    std::vector<std::unique_ptr<Node>> var_dec_list;
    SpecType spec_type;
};
class CompSt : public Stmt
{
public:
    std::vector<std::unique_ptr<Node>> def_list;
    std::vector<std::unique_ptr<Node>> stmt_list;
};
class ReturnStmt : public Stmt
{
public:
    std::unique_ptr<Node> ret;
};
class ExpStmt : public Stmt
{
public:
    std::unique_ptr<Node> exp;
};
class IfStmt : public Stmt
{
public:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> then_stmt;
    std::unique_ptr<Node> else_stmt;
};

class WhileStmt : public Stmt
{
public:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> body;
};
class FunDec : public ExtDef
{
public:
    std::string name;
    std::vector<std::unique_ptr<Node>> param_dec_list;
    std::unique_ptr<Node> comp_st;
    SpecType spec_type;
};
class VarDec : public Node
{
public:
    NodeSubType sub_type;
    std::string name;
};
class ParamDec : public Node
{
public:
    SpecType spec_type;
    std::unique_ptr<Node> var_dec;
};
class ElemDec : public VarDec
{
public:
};
class ArrayDec : public VarDec
{
public:
    std::vector<int> dims;
};
class Program : public Node
{
public:
    std::vector<std::unique_ptr<Node>> ExtDefList;
};
static void error(std::string msg)
{
    std::cout << msg << std::endl;
}
static SpecType get_spec_type(cJSON *node)
{
    std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));
    if (sub_type == "int")
    {
        return SpecType::Int;
    }
    else if (sub_type == "float")
    {
        return SpecType::Float;
    }
    else if (sub_type == "void")
    {
        return SpecType::Void;
    }
    else if (sub_type == "name")
    {
        return SpecType::Name;
    }
    else
    {
        error("get_spec_type error");
        return SpecType::Int;
    }
}
static std::vector<int> get_array_dims(cJSON *arr, std::string &name)
{
    std::vector<int> dims;
    std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(arr, "sub_type"));
    cJSON *size = nullptr;
    while (arr != nullptr)
    {
        if (sub_type == "array")
        {
            size = cJSON_GetObjectItem(arr, "size");
            dims.push_back(std::stoi(cJSON_GetStringValue(cJSON_GetObjectItem(size, "value"))));
            arr = cJSON_GetObjectItem(arr, "VarDec");
            sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(arr, "sub_type"));
        }
        else
        {
            name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(arr, "name"), "value"));
            arr = nullptr;
        }
    }
    // 翻转
    // std::reverse(dims.begin(), dims.end());
    return dims;
}
static std::unique_ptr<Node> parse_raw_ast(cJSON *node)
{
    std::string type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "type"));
    std::string sub_type;
    static SpecType def_spec_type;
    if (cJSON_GetObjectItem(node, "sub_type") != nullptr)
    {
        sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));
    }
    if (type == "Program")
    {
        int ExtDefList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "ExtDefList"));
        auto program = std::make_unique<Program>();
        program->type = NodeType::Program;
        for (int i = 0; i < ExtDefList_size; i++)
        {
            auto ExtDef = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "ExtDefList"), i);
            program->ExtDefList.push_back(std::move(parse_raw_ast(ExtDef)));
        }
        return program;
    }
    else if (type == "ExtDef")
    {
        if (sub_type == "FunDec")
        {
            auto fun_dec = std::make_unique<FunDec>();
            fun_dec->type = NodeType::ExtDef;
            fun_dec->sub_type = NodeSubType::FunDec;
            auto sub_node = cJSON_GetObjectItem(node, "FunDec");
            fun_dec->name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(sub_node, "name"), "value"));
            fun_dec->spec_type = get_spec_type(cJSON_GetObjectItem(node, "Specifier"));
            auto var_list_size = cJSON_GetArraySize(cJSON_GetObjectItem(sub_node, "VarList"));
            for (int i = 0; i < var_list_size; i++)
            {
                auto var = cJSON_GetArrayItem(cJSON_GetObjectItem(sub_node, "VarList"), i);
                auto param_dec = std::make_unique<ParamDec>();
                param_dec->type = NodeType::ParamDec;
                param_dec->spec_type = get_spec_type(cJSON_GetObjectItem(var, "Specifier"));
                param_dec->var_dec = std::move(parse_raw_ast(cJSON_GetObjectItem(var, "VarDec")));
                fun_dec->param_dec_list.push_back(std::move(param_dec));
            }
            fun_dec->comp_st = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "CompSt")));
            return fun_dec;
        }
        else if (sub_type == "ExtDecList")
        {
            auto ext_dec_list = std::make_unique<ExtDecList>();
            ext_dec_list->type = NodeType::ExtDef;
            ext_dec_list->sub_type = NodeSubType::ExtDecList;
            ext_dec_list->spec_type = get_spec_type(cJSON_GetObjectItem(node, "Specifier"));
            int var_dec_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "ExtDecList"));
            for (int i = 0; i < var_dec_size; i++)
            {
                auto var_dec = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "ExtDecList"), i);
                ext_dec_list->var_dec_list.push_back(std::move(parse_raw_ast(var_dec)));
            }
            return ext_dec_list;
        }
        else
        {
            error("ExtDef");
        }
    }
    else if (type == "Stmt")
    {
        if (sub_type == "CompSt")
        {
            auto DefList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "DefList"));
            auto StmtList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "StmtList"));
            auto comp_st = std::make_unique<CompSt>();
            comp_st->type = NodeType::Stmt;
            comp_st->sub_type = NodeSubType::CompSt;
            for (int i = 0; i < DefList_size; i++)
            {
                auto Def = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "DefList"), i);
                comp_st->def_list.push_back(std::move(parse_raw_ast(Def)));
            }
            for (int i = 0; i < StmtList_size; i++)
            {
                auto Stmt = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "StmtList"), i);
                comp_st->stmt_list.push_back(std::move(parse_raw_ast(Stmt)));
            }
            return comp_st;
        }
        else if (sub_type == "ReturnStmt")
        {
            auto return_stmt = std::make_unique<ReturnStmt>();
            return_stmt->type = NodeType::Stmt;
            return_stmt->sub_type = NodeSubType::ReturnStmt;
            return_stmt->ret = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp")));
            return return_stmt;
        }
        else if (sub_type == "ExpStmt")
        {
            auto exp_stmt = std::make_unique<ExpStmt>();
            exp_stmt->type = NodeType::Stmt;
            exp_stmt->sub_type = NodeSubType::ExpStmt;
            exp_stmt->exp = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp")));
            return exp_stmt;
        }
        else if (sub_type == "IfStmt" || sub_type == "IfElseStmt")
        {
            auto if_stmt = std::make_unique<IfStmt>();
            if_stmt->type = NodeType::Stmt;
            if_stmt->sub_type = NodeSubType::IfStmt;
            if_stmt->cond = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp")));
            if_stmt->then_stmt = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Stmt")));
            if (cJSON_GetObjectItem(node, "ElseStmt") != nullptr)
            {
                if_stmt->else_stmt = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "ElseStmt")));
            }
            return if_stmt;
        }
        else if (sub_type == "WhileStmt")
        {
            auto while_stmt = std::make_unique<WhileStmt>();
            while_stmt->type = NodeType::Stmt;
            while_stmt->sub_type = NodeSubType::WhileStmt;
            while_stmt->cond = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp")));
            while_stmt->body = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Stmt")));
            return while_stmt;
        }
        else if (sub_type == "ForStmt")
        {
            // 将for语句转换为while语句
            auto for_stmt = std::make_unique<CompSt>();
            for_stmt->type = NodeType::Stmt;
            for_stmt->sub_type = NodeSubType::CompSt;

            auto assign_stmt = std::make_unique<ExpStmt>();
            assign_stmt->type = NodeType::Stmt;
            assign_stmt->sub_type = NodeSubType::ExpStmt;
            assign_stmt->exp = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp1")));

            auto while_stmt = std::make_unique<WhileStmt>();
            while_stmt->type = NodeType::Stmt;
            while_stmt->sub_type = NodeSubType::WhileStmt;
            while_stmt->cond = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp2")));

            auto body_stmt = std::make_unique<CompSt>();
            body_stmt->type = NodeType::Stmt;
            body_stmt->sub_type = NodeSubType::CompSt;
            body_stmt->stmt_list.push_back(std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Stmt"))));
            auto assign_stmt2 = std::make_unique<ExpStmt>();
            assign_stmt2->type = NodeType::Stmt;
            assign_stmt2->sub_type = NodeSubType::ExpStmt;
            assign_stmt2->exp = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp3")));
            body_stmt->stmt_list.push_back(std::move(assign_stmt2));

            while_stmt->body = std::move(body_stmt);

            for_stmt->stmt_list.push_back(std::move(assign_stmt));
            for_stmt->stmt_list.push_back(std::move(while_stmt));

            return for_stmt;
        }
        else
        {
            error("Stmt");
        }
    }
    else if (type == "VarDec")
    {
        if (sub_type == "elem")
        {
            auto elem_dec = std::make_unique<ElemDec>();
            elem_dec->type = NodeType::VarDec;
            elem_dec->sub_type = NodeSubType::ElemDec;
            elem_dec->name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
            return elem_dec;
        }
        else if (sub_type == "array")
        {
            auto array_dec = std::make_unique<ArrayDec>();
            array_dec->type = NodeType::VarDec;
            array_dec->sub_type = NodeSubType::ArrayDec;
            array_dec->dims = get_array_dims(node, array_dec->name);
            return array_dec;
        }
        else
        {
            error("VarDec");
        }
    }
    else if (type == "Def")
    {
        auto def = std::make_unique<Def>();
        def->spec_type = get_spec_type(cJSON_GetObjectItem(node, "Specifier"));
        def_spec_type = def->spec_type;
        def->type = NodeType::Def;
        auto DecList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "DecList"));
        for (int i = 0; i < DecList_size; i++)
        {
            auto dec = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "DecList"), i);
            def->dec_list.push_back(std::move(parse_raw_ast(dec)));
        }
        return def;
    }
    else if (type == "Dec")
    {
        auto dec = std::make_unique<Dec>();
        dec->var_dec = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "VarDec")));
        dec->type = NodeType::Dec;
        dec->spec_type = def_spec_type;
        if (cJSON_GetObjectItem(node, "Exp") != nullptr)
        {
            dec->exp = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp")));
        }
        return dec;
    }
    else if (type == "Exp")
    {
        if (sub_type == "BinaryExp")
        {
            auto binary_exp = std::make_unique<BinaryExp>();
            std::string op = cJSON_GetStringValue(cJSON_GetObjectItem(node, "op"));
            auto lhs = cJSON_GetObjectItem(node, "Exp1");
            auto rhs = cJSON_GetObjectItem(node, "Exp2");
            binary_exp->type = NodeType::Exp;
            binary_exp->sub_type = NodeSubType::BinaryExp;
            binary_exp->lhs = std::move(parse_raw_ast(lhs));
            binary_exp->rhs = std::move(parse_raw_ast(rhs));
            if (op == "==")
            {
                binary_exp->op = OpType::EQ;
            }
            else if (op == "!=")
            {
                binary_exp->op = OpType::NE;
            }
            else if (op == ">")
            {
                binary_exp->op = OpType::GT;
            }
            else if (op == ">=")
            {
                binary_exp->op = OpType::GE;
            }
            else if (op == "<")
            {
                binary_exp->op = OpType::LT;
            }
            else if (op == "<=")
            {
                binary_exp->op = OpType::LE;
            }
            else if (op == "+")
            {
                binary_exp->op = OpType::PLUS;
            }
            else if (op == "-")
            {
                binary_exp->op = OpType::MINUS;
            }
            else if (op == "*")
            {
                binary_exp->op = OpType::STAR;
            }
            else if (op == "/")
            {
                binary_exp->op = OpType::DIV;
            }
            else if (op == "&&")
            {
                binary_exp->op = OpType::AND;
            }
            else if (op == "||")
            {
                binary_exp->op = OpType::OR;
            }
            else if (op == "=")
            {
                binary_exp->op = OpType::ASSIGNOP;
            }
            return binary_exp;
        }
        else if (sub_type == "FuncCall")
        {
            auto funcall = std::make_unique<FuncCall>();
            funcall->type = NodeType::Exp;
            funcall->sub_type = NodeSubType::FuncCall;
            funcall->name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
            auto args_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "Args"));
            for (int i = 0; i < args_size; i++)
            {
                auto arg = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "Args"), i);
                funcall->args.push_back(std::move(parse_raw_ast(arg)));
            }
            return funcall;
        }
        else if (sub_type == "ArrayExp")
        {
            auto array_exp = std::make_unique<ArrayExp>();
            array_exp->type = NodeType::Exp;
            array_exp->sub_type = NodeSubType::ArrayExp;
            array_exp->array = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp1")));
            array_exp->index = std::move(parse_raw_ast(cJSON_GetObjectItem(node, "Exp2")));
            return array_exp;
        }
        else
        {
            error("Exp");
        }
    }
    else if (type == "id")
    {
        auto basic_exp = std::make_unique<BasicExp>();
        basic_exp->type = NodeType::Exp;
        basic_exp->sub_type = NodeSubType::BasicExp;
        basic_exp->spec_type = SpecType::Name;
        basic_exp->name_val = cJSON_GetStringValue(cJSON_GetObjectItem(node, "value"));
        return basic_exp;
    }
    else if (type == "number")
    {
        auto basic_exp = std::make_unique<BasicExp>();
        basic_exp->type = NodeType::Exp;
        basic_exp->sub_type = NodeSubType::BasicExp;
        basic_exp->spec_type = SpecType::Int;
        basic_exp->int_val = std::stoi(cJSON_GetStringValue(cJSON_GetObjectItem(node, "value")));
        return basic_exp;
    }
    else if (type == "real")
    {
        auto basic_exp = std::make_unique<BasicExp>();
        basic_exp->type = NodeType::Exp;
        basic_exp->sub_type = NodeSubType::BasicExp;
        basic_exp->spec_type = SpecType::Float;
        basic_exp->float_val = std::stoi(cJSON_GetStringValue(cJSON_GetObjectItem(node, "value")));
        return basic_exp;
    }
    return nullptr;
}