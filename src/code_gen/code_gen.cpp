#include "code_gen.h"
LLVMContext context;

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

template <NodeType type>
void visitor<type>::code_gen(cJSON *node)
{
    ErrorV("Not implemented");
}

Value *visitor<NodeType::Program>::code_gen(cJSON *node)
{
    return ErrorV("Not implemented");
};

Value *visitor<NodeType::Number>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    const char *value = cJSON_GetStringValue(cJSON_GetObjectItem(node, "value"));
    return ConstantInt::get(context, APInt(32, atoi(value)));
}

Value *visitor<NodeType::ID>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    Value *v = NamedValues[cJSON_GetStringValue(node)];
    return v ? v : ErrorV("Unknown variable name");
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
        // std::cout << L << "+" << R << std::endl;
        println(L, "+", R);
        return Builder.CreateAdd(L, R, "addtmp");
    }
    else if (Op == "-")
    {
        // std::cout << L << "-" << R << std::endl;
        println(L, "-", R);
        return Builder.CreateSub(L, R, "subtmp");
    }
    else if (Op == "*")
    {
        // std::cout << L << "*" << R << std::endl;
        println(L, "*", R);
        return Builder.CreateMul(L, R, "multmp");
    }
    else if (Op == "/")
    {
        // std::cout << L << "/" << R << std::endl;
        println(L, "/", R);
        return Builder.CreateSDiv(L, R, "divtmp");
    }
    else if (Op == "<")
    {
        println(L, "<", R);
        L = Builder.CreateICmpULT(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == ">")
    {
        println(L, ">", R);
        L = Builder.CreateICmpUGT(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "==")
    {
        println(L, "==", R);
        L = Builder.CreateICmpEQ(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "!=")
    {
        println(L, "!=", R);
        L = Builder.CreateICmpNE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "<=")
    {
        println(L, "<=", R);
        L = Builder.CreateICmpULE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == ">=")
    {
        println(L, ">=", R);
        L = Builder.CreateICmpUGE(L, R, "cmptmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "&&")
    {
        println(L, "&&", R);
        L = Builder.CreateICmpNE(L, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        R = Builder.CreateICmpNE(R, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        L = Builder.CreateAnd(L, R, "andtmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
    }
    else if (Op == "||")
    {
        println(L, "||", R);
        L = Builder.CreateICmpNE(L, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        R = Builder.CreateICmpNE(R, ConstantInt::get(context, APInt(32, 0)), "cmptmp");
        L = Builder.CreateOr(L, R, "ortmp");
        return Builder.CreateZExt(L, Type::getInt32Ty(context), "booltmp");
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
    }
    else if (type == "number")
    {
        return visitor<NodeType::Number>::code_gen(node);
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
            visitor<NodeType::FunDec>::code_gen(cJSON_GetObjectItem(node, "FunDec"));
        }
    }
}

Function *visitor<NodeType::FunDec>::code_gen(cJSON *node)
{
    assert(node != nullptr);
    int var_size = cJSON_GetArraySize(cJSON_GetObjectItem(node, "VarList"));
    std::vector<Type *> arg_types(var_size, Type::getInt32Ty(context));
    FunctionType *func_type = FunctionType::get(Type::getInt32Ty(context), arg_types, false);

    std::string func_name = cJSON_GetStringValue(cJSON_GetObjectItem(node, "name"));
    Function *F = Function::Create(func_type, Function::ExternalLinkage, func_name, TheModule);
    //先不判断重名情况

    //设置参数名
    int i = 0;
    for (auto &arg : F->args())
    {
        char *var_name = cJSON_GetStringValue(cJSON_GetArrayItem(cJSON_GetObjectItem(node, "VarList"), i));
        arg.setName(var_name);
        NamedValues[var_name] = &arg;
        i++;
    }

    //创建函数体
    NamedValues.clear();

    BasicBlock *BB = BasicBlock::Create(context, "entry", F);
    Builder.SetInsertPoint(BB);

    for (auto &arg : F->args())
    {
        //为参数分配空间
        AllocaInst *Alloca = Builder.CreateAlloca(Type::getInt32Ty(context), 0, arg.getName());
        Builder.CreateStore(&arg, Alloca);
        NamedValues[arg.getName().data()] = Alloca;
    }

    cJSON *CompSt = cJSON_GetObjectItem(node, "CompSt");
    if (Value *ret = visitor<NodeType::CompSt>::code_gen(CompSt))
    {
        Builder.CreateRet(ret);
        if (verifyFunction(*F))
        {
            F->eraseFromParent();
            return nullptr;
        }
        return F;
    }
    else
    {
        Builder.CreateRetVoid();
        if (verifyFunction(*F))
        {
            F->eraseFromParent();
            return nullptr;
        }
        return F;
    }
}

Value *visitor<NodeType::FunCall>::code_gen(cJSON *node)
{
    Function *CalleeF = TheModule->getFunction(cJSON_GetStringValue(cJSON_GetObjectItem(node, "name")));
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
    return nullptr;
}
