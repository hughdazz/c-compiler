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
static Type *get_dec_type(cJSON *node)
{
    std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));
    if (sub_type == "elem")
    {
        param_name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
        return Type::getInt32Ty(context);
    }
    else
    {
        // array
        int size = atoi(cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "size"), "value")));

        cJSON *VarDec = cJSON_GetObjectItem(node, "VarDec");
        return ArrayType::get(get_dec_type(VarDec), size);
    }
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
    std::vector<Type *> arg_types;
    std::vector<std::string> arg_names;
    for (int i = 0; i < var_size; i++)
    {
        cJSON *ParamDec = cJSON_GetArrayItem(cJSON_GetObjectItem(node, "VarList"), i);
        cJSON *VarDec = cJSON_GetObjectItem(ParamDec, "VarDec");
        arg_types.push_back(get_dec_type(VarDec));
        arg_names.push_back(param_name);
    }
    FunctionType *func_type = FunctionType::get(Type::getInt32Ty(context), arg_types, false);
    std::string func_name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
    Function *F = Function::Create(func_type, Function::ExternalLinkage, func_name, TheModule);
    //先不判断重名情况

    //设置参数名
    int i = 0;
    for (auto &arg : F->args())
    {
        arg.setName(arg_names[i]);
        if (NamedScopes.find(func_name) == NamedScopes.end())
        {
            NamedScopes[func_name] = std::map<std::string, Value *>();
            NamedScopes[func_name][arg_names[i]] = &arg;
        }
        else
        {
            NamedScopes[func_name][arg_names[i]] = &arg;
        }
        i++;
    }
    //创建函数体
    BasicBlock *BB = BasicBlock::Create(context, "entry", F);
    Builder.SetInsertPoint(BB);
    i = 0;
    for (auto &arg : F->args())
    {
        //为参数分配空间
        AllocaInst *Alloca = Builder.CreateAlloca(arg_types[i], 0, arg.getName());
        Builder.CreateStore(&arg, Alloca);
        //在NamedScope中加入参数
        NamedScopes[F->getName().str()][arg.getName().str()] = Alloca;
        i++;
    }

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
    std::string Op = cJSON_GetStringValue(cJSON_GetObjectItem(node, "op"));

    // 判断L是否是指针，如果是则Load
    if (L->getType()->isPointerTy() && Op != "=")
    {
        L = Builder.CreateLoad(L);
    }
    // 判断R是否是指针，如果是则Load
    if (R->getType()->isPointerTy())
    {
        R = Builder.CreateLoad(R);
    }

    if (L == nullptr || R == nullptr)
    {
        ErrorV("Invalid binary expression");
        return nullptr;
    }
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
        // 查找左值
        Function *F = Builder.GetInsertBlock()->getParent();
        Value *V = get_lvalue(F->getName(), L->getName());
        if (V == nullptr)
        {
            V = L;
        }
        Builder.CreateStore(R, V);

        return V;
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
        else if (sub_type == "ArrayExp")
        {
            Value *ret = visitor<NodeType::Array>::code_gen(node);
            Function *F = Builder.GetInsertBlock()->getParent();
            return ret;
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
            visitor<NodeType::Stmt>::code_gen(CompSt);
            F->getBasicBlockList().push_back(ReturnBB);
            Builder.SetInsertPoint(ReturnBB);
            Value *ret = get_lvalue(F->getName(), "return_ptr");
            ret = Builder.CreateLoad(ret, "return_val");
            Builder.CreateRet(ret);
            if (verifyFunction(*F, &errs()))
            {
                F->print(errs());
                F->eraseFromParent();
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
    // 获取F entry block
    BasicBlock &BB = F->getBasicBlockList().back();
    // 设置插入点
    Builder.SetInsertPoint(&BB, BB.end());

    // 为返回值分配空间
    AllocaInst *Alloca = Builder.CreateAlloca(Type::getInt32Ty(context), 0, "return_ptr");
    NamedScopes[F->getName().str()]["return_ptr"] = Alloca;
    // 创建ReturnBlock
    ReturnBB = BasicBlock::Create(context, "return");
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
        Value *arg = visitor<NodeType::Exp>::code_gen(cJSON_GetArrayItem(cJSON_GetObjectItem(node, "Args"), i));
        if (arg == nullptr)
        {
            return nullptr;
        }
        if (arg->getType()->isPointerTy())
        {
            arg = Builder.CreateLoad(arg, "param");
        }
        ArgsV.push_back(arg);
    }
    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");
}

void visitor<NodeType::CompSt>::code_gen(cJSON *node)
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
        visitor<NodeType::Stmt>::code_gen(stmt);
    }
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

void visitor<NodeType::ReturnStmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Value *ret = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    //
    Function *F = Builder.GetInsertBlock()->getParent();
    std::string scope_name = F->getName().data();
    Value *ret_ptr = get_lvalue(scope_name, "return_ptr");
    // 判断ret是否是指针(左值)
    if (ret->getType()->isPointerTy())
    {
        ret = Builder.CreateLoad(ret);
    }
    Builder.CreateStore(ret, ret_ptr);
    // 创建br到return block
    Builder.CreateBr(ReturnBB);
}
void visitor<NodeType::Stmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    if (Builder.GetInsertBlock()->getTerminator() != nullptr)
    {
        return;
    }

    std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(node, "sub_type"));

    if (sub_type == "ReturnStmt")
    {
        visitor<NodeType::ReturnStmt>::code_gen(node);
    }
    else if (sub_type == "ExpStmt")
    {
        visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    }
    else if (sub_type == "IfStmt" || sub_type == "IfElseStmt")
    {
        visitor<NodeType::IfStmt>::code_gen(node);
    }
    else if (sub_type == "WhileStmt")
    {
        visitor<NodeType::WhileStmt>::code_gen(node);
    }
    else if (sub_type == "CompSt")
    {
        visitor<NodeType::CompSt>::code_gen(node);
    }
}

void visitor<NodeType::IfStmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Value *cond = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    if (cond == nullptr)
    {
        return;
    }

    cond = Builder.CreateICmpNE(cond, ConstantInt::get(context, APInt(32, 0, true)), "ifcond");

    Function *F = Builder.GetInsertBlock()->getParent();

    BasicBlock *ThenBB = BasicBlock::Create(context, "ifthen", F);
    BasicBlock *ElseBB = BasicBlock::Create(context, "ifelse");
    BasicBlock *MergeBB = BasicBlock::Create(context, "ifcont");

    Builder.CreateCondBr(cond, ThenBB, ElseBB);

    // 插入then块
    Builder.SetInsertPoint(ThenBB);
    // 产生then块的代码，没有返回值，不过当然可以写return
    visitor<NodeType::Stmt>::code_gen(cJSON_GetObjectItem(node, "Stmt"));
    // 判断是否有return语句，如果没有，就插入br到merge块
    if (Builder.GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder.CreateBr(MergeBB);
    }
    // 更新then块
    ThenBB = Builder.GetInsertBlock();

    // 插入else块
    F->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);
    // 产生else块的代码
    if (cJSON_GetObjectItem(node, "ElseStmt") != nullptr)
    {
        visitor<NodeType::Stmt>::code_gen(cJSON_GetObjectItem(node, "ElseStmt"));
    }
    // 判断是否有return语句，如果没有，就插入br到merge块
    if (Builder.GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder.CreateBr(MergeBB);
    }
    // 更新else块:并不需要，因为后面不会用到
    ElseBB = Builder.GetInsertBlock();
    // 插入merge块
    F->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
}

void visitor<NodeType::WhileStmt>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Function *F = Builder.GetInsertBlock()->getParent();

    BasicBlock *CondBB = BasicBlock::Create(context, "whilecond", F);
    BasicBlock *BodyBB = BasicBlock::Create(context, "whilebody");
    BasicBlock *MergeBB = BasicBlock::Create(context, "whilecont");

    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(CondBB);
    Value *cond = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
    if (cond == nullptr)
    {
        return;
    }
    cond = Builder.CreateICmpNE(cond, ConstantInt::get(context, APInt(32, 0, true)), "whilecond");
    Builder.CreateCondBr(cond, BodyBB, MergeBB);

    F->getBasicBlockList().push_back(BodyBB);
    Builder.SetInsertPoint(BodyBB);
    visitor<NodeType::Stmt>::code_gen(cJSON_GetObjectItem(node, "Stmt"));
    if (Builder.GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder.CreateBr(CondBB);
    }

    F->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
}

void visitor<NodeType::Def>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    cJSON *DecList = cJSON_GetObjectItem(node, "DecList");
    int DecList_size = cJSON_GetArraySize(DecList);
    for (int i = 0; i < DecList_size; i++)
    {
        cJSON *Dec = cJSON_GetArrayItem(DecList, i);
        cJSON *VarDec = cJSON_GetObjectItem(Dec, "VarDec");
        std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(VarDec, "sub_type"));
        if (sub_type == "elem")
        {
            // elem
            visitor<NodeType::ElemDec>::code_gen(VarDec);
        }
        else
        {
            // array
            visitor<NodeType::ArrayDec>::code_gen(VarDec);
        }
    }
}

Value *visitor<NodeType::ElemDec>::code_gen(cJSON *node)
{
    std::string ElemDec_name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(node, "name"), "value"));
    AllocaInst *Alloca = Builder.CreateAlloca(Type::getInt32Ty(context), nullptr, ElemDec_name);
    // 未初始化则赋值为0
    if (cJSON_GetObjectItem(node, "Exp") != nullptr)
    {
        Value *init = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp"));
        if (init == nullptr)
        {
            return nullptr;
        }
        Builder.CreateStore(init, Alloca);
    }
    else
    {
        Builder.CreateStore(ConstantInt::get(context, APInt(32, 0, true)), Alloca);
    }
    Function *F = Builder.GetInsertBlock()->getParent();
    NamedScopes[F->getName().str()][ElemDec_name] = Alloca;
}

Value *visitor<NodeType::ArrayDec>::code_gen(cJSON *node)
{
    std::vector<int> dim;
    cJSON *VarDec = node;
    std::string array_name;
    while (cJSON_GetObjectItem(VarDec, "sub_type") != nullptr)
    {
        std::string sub_type = cJSON_GetStringValue(cJSON_GetObjectItem(VarDec, "sub_type"));
        if (sub_type == "array")
        {
            int size = atoi(cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(VarDec, "size"), "value")));
            dim.push_back(size);
            VarDec = cJSON_GetObjectItem(VarDec, "VarDec");
        }
        else
        {
            array_name = cJSON_GetStringValue(cJSON_GetObjectItem(cJSON_GetObjectItem(VarDec, "name"), "value"));
            break;
        }
    }
    // 生成数组
    Type *array_type = Type::getInt32Ty(context);
    for (int i = 0; i < dim.size(); i++)
    {
        array_type = ArrayType::get(array_type, dim[i]);
    }
    AllocaInst *Alloca = Builder.CreateAlloca(array_type, nullptr, array_name);

    // 将数组放入符号表
    Function *F = Builder.GetInsertBlock()->getParent();
    NamedScopes[F->getName().str()][array_name] = Alloca;
}
Value *visitor<NodeType::Array>::code_gen(cJSON *node)
{
    std::cout << cJSON_Print(node) << std::endl;
    cJSON *origin = cJSON_GetObjectItem(node, "Exp1");
    std::string origin_type = cJSON_GetStringValue(cJSON_GetObjectItem(origin, "type"));
    Value *idx = nullptr;
    idx = visitor<NodeType::Exp>::code_gen(cJSON_GetObjectItem(node, "Exp2"));
    // 判断idx是否是指针类型
    if (idx->getType()->isPointerTy())
    {
        idx = Builder.CreateLoad(idx);
    }
    if (origin_type == "id")
    {
        array_name = cJSON_GetStringValue(cJSON_GetObjectItem(origin, "value"));
        Function *F = Builder.GetInsertBlock()->getParent();
        Value *array = NamedScopes[F->getName().str()][array_name];
        return Builder.CreateGEP(array, {ConstantInt::get(context, APInt(32, 0, true)), idx});
    }
    else
    {
        Value *origin_ptr = visitor<NodeType::Array>::code_gen(origin);
        return Builder.CreateGEP(origin_ptr, {ConstantInt::get(context, APInt(32, 0, true)), idx});
    }
}
