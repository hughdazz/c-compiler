#include "code_gen.h"

static std::ostream &operator<<(std::ostream &out, Value *v)
{
    assert(v != nullptr);
    std::string s;
    raw_string_ostream os(s);
    v->print(os);
    out << s;
}
static void println()
{
    std::cout << std::endl;
}
template <typename T, typename... Args>
static void println(T value, Args... args)
{
    std::cout << value;
    println(args...);
}
static Value *get_lvalue(StringRef scope_name, StringRef var_name)
{
    auto scope = NamedScopes.find(scope_name.str());
    if (scope == NamedScopes.end())
    {
        return ErrorV("Unknown scope");
    }
    auto var = scope->second.find(var_name.str());
    if (var == scope->second.end())
    {
        return ErrorV("Unknown variable name");
    }
    return var->second;
}

template <NodeType type>
void visitor<type>::code_gen(cJSON *node)
{
    ErrorV("Not implemented");
}

void visitor<NodeType::Program>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    cJSON *ExtDefList = cJSON_GetObjectItem(node, "ExtDefList");
    // 将所有函数定义的声明加入程序头部
    for (int i = 0; i < cJSON_GetArraySize(ExtDefList); i++)
    {
        cJSON *ExtDef = cJSON_GetArrayItem(ExtDefList, i);
        std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(ExtDef, "sub_type"));
        if (sub_type == "FunDec")
        {
            visitor<NodeType::ExtProtoType>::code_gen(cJSON_GetObjectItem(ExtDef, "FunDec"));
        }
    }
    for (cJSON *ExtDef = ExtDefList->child; ExtDef != nullptr; ExtDef = ExtDef->next)
    {
        visitor<NodeType::ExtDef>::code_gen(ExtDef);
    }
};
Function *visitor<NodeType::ExtProtoType>::code_gen(cJSON *node)
{
    int var_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "VarList"));
    std::vector<Type *> arg_types(var_size, Type::getInt32Ty(context));
    FunctionType *func_type = FunctionType::get(Type::getInt32Ty(context), arg_types, false);

    std::string func_name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
    Function *F = Function::Create(func_type, Function::ExternalLinkage, func_name, TheModule);
    //先不判断重名情况

    //设置参数名
    int i = 0;
    for (auto &arg : F->args())
    {
        cJSON *var = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "VarList"), i);
        cJSON *var_dec_name = cJSON_GetObjectItem(cJSON_GetObjectItem(var, "VarDec"), "name");
        char *var_name = cJSON_GetStringValue(cJSON_GetObjectItem(var_dec_name, "value"));
        arg.setName(var_name);
        if (NamedScopes.find(func_name) == NamedScopes.end())
        {
            NamedScopes[func_name] = std::map<std::string, Value *>();
            NamedScopes[func_name][var_name] = &arg;
        }
        else
        {
            NamedScopes[func_name][var_name] = &arg;
        }
        i++;
    }
    //声明

    return F;
}

Value *visitor<NodeType::Number>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    const char *value = cJSON_GetStringValue(cJSON_GetObjectItem(node, "value"));
    return ConstantInt::get(context, APInt(32, atoi(value)));
}

Value *visitor<NodeType::BinaryExr>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Value *L = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp1"));
    Value *R = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp2"));
    if (L == nullptr || R == nullptr)
    {
        ErrorV("Invalid binary expression");
        return nullptr;
    }
    std::string Op = cJSON_GetStringValue(cJSON_GetObjectItem(node, "op"));
    if (Op == "+")
    {
        return Builder.CreateAdd(L, R, "addtmp");
    }
    else if (Op == "-")
    {
        return Builder.CreateSub(L, R, "subtmp");
    }
    else if (Op == "*")
    {
        return Builder.CreateMul(L, R, "multmp");
    }
    else if (Op == "/")
    {
        return Builder.CreateSDiv(L, R, "divtmp");
    }
    else if (Op == "<")
    {
        L = Builder.CreateICmpULT(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == ">")
    {
        L = Builder.CreateICmpUGT(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "==")
    {
        L = Builder.CreateICmpEQ(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "!=")
    {
        L = Builder.CreateICmpNE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "<=")
    {
        L = Builder.CreateICmpULE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == ">=")
    {
        L = Builder.CreateICmpUGE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "&&")
    {
        L = Builder.CreateICmpNE(L, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        R = Builder.CreateICmpNE(R, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        L = Builder.CreateAnd(L, R, "andtmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "||")
    {
        L = Builder.CreateICmpNE(L, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        R = Builder.CreateICmpNE(R, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        L = Builder.CreateOr(L, R, "ortmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "=")
    {
        // 创建指针
        AllocaInst *Alloca = Builder.CreateAlloca(Type::getInt32Ty(context), nullptr, "ptrtmp");
        // 将右值赋值给指针指向的内存
        Builder.CreateStore(R, Alloca);
        // 查找L是否存在，不存在则代表赋值给了右值，这是个错误
        // 存在则更改原左值为现在的临时变量
        Function *F = Builder.GetInsertBlock()->getParent();

        Value *V = get_lvalue(F->getName(), L->getName());
        if (V == nullptr)
        {
            ErrorV("Invalid assignment");
            return nullptr;
        }
        // 创建临时变量，并Load
        Value *Tmp = Builder.CreateLoad(Alloca, "assigntmp");
        // 更改原左值
        NamedScopes[F->getName().str()][L->getName().str()] = Tmp;
        return Tmp;
    }
    else
    {
        return ErrorV("Invalid binary operator");
    }
    return nullptr;
}
Value *visitor<NodeType::Exp>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    std::string type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "type"));
    if (type == "Exp")
    {
        std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));
        if (sub_type == "BinaryExp")
        {
            return visitor<NodeType::BinaryExr>::code_gen(node);
        }
        else if (sub_type == "FuncCall")
        {
            return visitor<NodeType::FuncCall>::code_gen(node);
        }
    }
    else if (type == "number")
    {
        return visitor<NodeType::Number>::code_gen(node);
    }
    else if (type == "id")
    {
        return visitor<NodeType::Variable>::code_gen(node);
    }
    return nullptr;
}

void visitor<NodeType::ExtDef>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    std::string type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "type"));
    if (type == "ExtDef")
    {
        std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));
        if (sub_type == "ExtDecList")
        {
        }
        else if (sub_type == "FunDec")
        {
            Function *F = visitor<NodeType::FunDec>::code_gen(cJSON_GetObjectItem(node, "FunDec"));
            cJSON *CompSt = cJSON_GetObjectItem(node, "CompSt");
            if (Value *ret = visitor<NodeType::CompSt>::code_gen(CompSt))
            {
                Builder.CreateRet(ret);
                if (verifyFunction(*F, &errs()))
                {
                    F->eraseFromParent();
                }
            }
            else
            {
                Builder.CreateRetVoid();
                if (verifyFunction(*F, &errs()))
                {
                    F->eraseFromParent();
                }
            }
        }
    }
}

Function *visitor<NodeType::FunDec>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    // 获取函数名
    std::string name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
    // 获取函数指针
    Function *F = TheModule->getFunction(name);
    if (F == nullptr)
    {
        return nullptr;
    }
    //创建函数体
    BasicBlock *BB = BasicBlock::Create(context, "entry", F);
    Builder.SetInsertPoint(BB);

    for (auto &arg : F->args())
    {
        // //为参数分配空间
        // AllocaInst *Alloca = Builder.CreateAlloca(Type::getInt32Ty(context), 0, arg.getName());
        // Builder.CreateStore(&arg, Alloca);
        // NamedValues[arg.getName().data()] = Alloca;
    }
    return F;
}

Value *visitor<NodeType::FuncCall>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    cJSON *func_name = cJSON_GetObjectItem(node, "name");
    Function *CalleeF = TheModule->getFunction(cJSON_GetStringValue(cJSON_GetObjectItem(func_name, "value")));
    if (CalleeF == nullptr)
    {
        return ErrorV("Unknown function referenced");
    }
    int arg_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "Args"));
    if (CalleeF->arg_size() != arg_size)
    {
        return ErrorV("Incorrect # arguments passed");
    }
    std::vector<Value *> ArgsV;
    for (int i = 0; i < arg_size; i++)
    {
        ArgsV.push_back(visitor<NodeType::Exp>::code_gen(cJSON_GetArrayItem(cJSON_GetObjectItem(node, "Args"), i)));
        if (ArgsV.back() == nullptr)
        {
            return nullptr;
        }
    }
    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

Value *visitor<NodeType::CompSt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    std::vector<cJSON *> DefList;
    std::vector<cJSON *> StmtList;
    int DefList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "DefList"));
    int StmtList_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "StmtList"));
    for (int i = 0; i < DefList_size; i++)
    {
        DefList.push_back(cJSON_GetArrayItem(cJSON_GetObjectItem(node, "DefList"), i));
    }
    for (int i = 0; i < StmtList_size; i++)
    {
        StmtList.push_back(cJSON_GetArrayItem(cJSON_GetObjectItem(node, "StmtList"), i));
    }
    for (auto &def : DefList)
    {
        visitor<NodeType::Def>::code_gen(def);
    }
    for (auto &stmt : StmtList)
    {
        if (Value *ret = visitor<NodeType::Stmt>::code_gen(stmt))
        {
            return ret;
        }
    }
    return nullptr;
}

Value *visitor<NodeType::Variable>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    std::string var_name = cJSON_GetStringValue(cJSON_GetObjectItem(node, "value"));
    // 获取当前作用域名
    Function *F = Builder.GetInsertBlock()->getParent();
    std::string scope_name = F->getName().data();

    return get_lvalue(scope_name, var_name);

    // Value *V = NamedValues[cJSON_GetStringValue(cJSON_GetObjectItem(node, "value"))];
    // if (V == nullptr)
    // {
    //     return ErrorV("Unknown variable name");
    // }
}

Value *visitor<NodeType::ReturnStmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Value *ret = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    if (ret == nullptr)
    {
        return nullptr;
    }
    return ret;
}
Value *visitor<NodeType::Stmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));

    if (sub_type == "ReturnStmt")
    {
        return visitor<NodeType::ReturnStmt>::code_gen(node);
    }
    else if (sub_type == "ExpStmt")
    {
        visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    }
    return nullptr;
}
