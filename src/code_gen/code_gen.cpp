#include "code_gen/code_gen.h"
template <>
void CodeGen::code_gen<FunDec>(FunDec *node);
template <>
void CodeGen::code_gen<Dec>(Dec *node);
template <>
void CodeGen::code_gen<Def>(Def *node);
template <>
void CodeGen::code_gen<ExpStmt>(ExpStmt *node);
template <>
void CodeGen::code_gen<IfStmt>(IfStmt *node);
template <>
void CodeGen::code_gen<WhileStmt>(WhileStmt *node);
template <>
void CodeGen::code_gen<ReturnStmt>(ReturnStmt *node);
template <>
void CodeGen::code_gen<CompSt>(CompSt *node);
template <>
void CodeGen::code_gen<Stmt>(Stmt *node);
template <>
void CodeGen::code_gen<ExtDef>(ExtDef *node);
template <>
void CodeGen::code_gen<Program>(Program *node);
template <>
void CodeGen::code_gen<ExtDecList>(ExtDecList *node);
template <>
void CodeGen::code_gen<ExtDecList>(ExtDecList *node)
{
    // 全局变量定义
    for (auto &var_dec : node->var_dec_list)
    {
        auto var_dec_ptr = (VarDec *)var_dec.get();
        auto var_type = gen_VarDec_Type(var_dec_ptr, get_type(node->spec_type));
        if (var_type == nullptr)
        {
            return;
        }
        auto var_name = var_dec_ptr->name;
        auto var = new GlobalVariable(*TheModule, var_type, false, GlobalValue::CommonLinkage, Constant::getNullValue(var_type), var_name);
        NamedScopes["global"][var_name] = var;
    }
}
CodeGen::CodeGen(Program *program) : program(program)
{
    Builder = std::make_unique<IRBuilder<>>(context);
    TheModule = std::make_unique<Module>("test", context);
    TheModule->setSourceFileName("test");
    code_gen(this->program);
    TheModule->print(errs(), nullptr);
}
CodeGen::CodeGen(std::string lib_path, Program *program) : program(program)
{
    Builder = std::make_unique<IRBuilder<>>(context);
    SMDiagnostic err;
    TheModule = parseIRFile("test.lib.ll", err, context);
    TheModule->setSourceFileName("test");
    code_gen(this->program);
    TheModule->print(errs(), nullptr);
}
Type *CodeGen::get_type(SpecType spec_type)
{
    switch (spec_type)
    {
    case SpecType::Int:
        return Type::getInt32Ty(context);
    case SpecType::Float:
        return Type::getFloatTy(context);
    case SpecType::Void:
        return Type::getVoidTy(context);
    default:
        return nullptr;
    }
}
Type *CodeGen::gen_VarDec_Type(VarDec *var_dec, Type *var_type)
{
    assert(var_dec != nullptr);
    if (var_dec->sub_type == NodeSubType::ElemDec)
    {
        return var_type;
    }
    else
    {
        // array
        ArrayDec *array_dec = (ArrayDec *)var_dec;
        Type *array_type = var_type;
        for (auto dim : array_dec->dims)
        {
            array_type = ArrayType::get(array_type, dim);
        }
        return array_type;
    }
}
void CodeGen::gen_ExtProtoType(FunDec *fun_dec)
{
    assert(fun_dec != nullptr);

    std::vector<Type *> arg_types;
    std::vector<std::string> arg_names;
    for (auto &param_dec : fun_dec->param_dec_list)
    {
        auto param_dec_ptr = (ParamDec *)param_dec.get();
        VarDec *var_dec = (VarDec *)(param_dec_ptr)->var_dec.get();
        Type *var_type = get_type(param_dec_ptr->spec_type);

        if (var_dec->sub_type == NodeSubType::ArrayDec)
        {
            arg_types.push_back(gen_VarDec_Type(var_dec, var_type));
        }
        else
        {
            arg_types.push_back(var_type);
        }
        arg_names.push_back(var_dec->name);
    }
    // 创建函数声明
    FunctionType *func_type = FunctionType::get(get_type(fun_dec->spec_type), arg_types, false);
    now_F = Function::Create(func_type, Function::ExternalLinkage, fun_dec->name, TheModule.get());
    for (int i = 0; i < arg_names.size(); i++)
    {
        now_F->getArg(i)->setName(arg_names[i]);
        if (NamedScopes.find(now_F->getName().str()) == NamedScopes.end())
        {
            NamedScopes[now_F->getName().str()] = std::map<std::string, Value *>();
            NamedScopes[now_F->getName().str()][arg_names[i]] = now_F->getArg(i);
        }
        else
        {
            NamedScopes[now_F->getName().str()][arg_names[i]] = now_F->getArg(i);
        }
    }
    // 创建函数体entry块
    BasicBlock *entry = BasicBlock::Create(context, "entry", now_F);
    Builder->SetInsertPoint(entry);

    for (int i = 0; i < arg_names.size(); i++)
    {
        //为参数分配空间先
        AllocaInst *alloca = Builder->CreateAlloca(get_type(fun_dec->spec_type), nullptr, arg_names[i]);
        Builder->CreateStore(now_F->getArg(i), alloca);
        //替换参数
        NamedScopes[now_F->getName().str()][arg_names[i]] = alloca;
    }
}

template <>
void CodeGen::code_gen<FunDec>(FunDec *node)
{
    assert(node != nullptr);
    // 获取函数名
    // 获取函数指针
    now_F = TheModule->getFunction(node->name);
    assert(now_F != nullptr);
    // 获取entry块
    BasicBlock &entry = now_F->getBasicBlockList().back();
    // 设置插入点
    Builder->SetInsertPoint(&entry, entry.end());

    // 为返回值分配空间
    AllocaInst *Alloca = Builder->CreateAlloca(get_type(node->spec_type), 0, "return_ptr");
    NamedScopes[now_F->getName().str()]["return_ptr"] = Alloca;
    // 创建ReturnBlock
    now_return = BasicBlock::Create(context, "return");

    // 生成函数体
    code_gen((CompSt *)node->comp_st.get());
    // 加入return块
    now_F->getBasicBlockList().push_back(now_return);
    // 设置插入点
    Builder->SetInsertPoint(now_return);
    // 返回值
    Value *return_ptr = NamedScopes[now_F->getName().str()]["return_ptr"];
    Value *ret = get_lvalue(now_F->getName().str(), "return_ptr");
    ret = Builder->CreateLoad(ret, "return_val");
    Builder->CreateRet(ret);
    if (verifyFunction(*now_F, &errs()))
    {
        now_F->print(errs());
        now_F->eraseFromParent();
    }
}
Value *CodeGen::gen_Exp(Exp *node)
{
    assert(node != nullptr);
    switch (node->sub_type)
    {
    case NodeSubType::BasicExp:
    {
        auto basic_exp = (BasicExp *)node;
        switch (basic_exp->spec_type)
        {
        case SpecType::Name:
            return get_lvalue(now_F->getName().str(), basic_exp->name_val);
        case SpecType::Int:
            return ConstantInt::get(Type::getInt32Ty(context), basic_exp->int_val);
        case SpecType::Float:
            return ConstantFP::get(Type::getFloatTy(context), basic_exp->float_val);
        }
        break;
    }
    case NodeSubType::BinaryExp:
    {
        auto binary_exp = (BinaryExp *)node;
        Value *lhs = gen_Exp((Exp *)binary_exp->lhs.get());
        Value *rhs = gen_Exp((Exp *)binary_exp->rhs.get());
        // 判断L是否是指针，如果是则Load
        if (lhs->getType()->isPointerTy() && binary_exp->op != OpType::ASSIGNOP)
        {
            lhs = Builder->CreateLoad(lhs);
        }
        // 判断R是否是指针，如果是则Load
        if (rhs->getType()->isPointerTy())
        {
            rhs = Builder->CreateLoad(rhs);
        }
        // 判断lhs,rhs是否是浮点数
        if ((lhs->getType()->isFloatTy() && rhs->getType()->isIntegerTy()) ||
            (lhs->getType()->isIntegerTy() && rhs->getType()->isFloatTy()))
        {
            // 不允许隐式转换
            put_error("not support implicit conversion");
        }
        bool is_int = lhs->getType()->isIntegerTy();
        if (is_int)
        {
            switch (binary_exp->op)
            {
            case OpType::PLUS:
                return Builder->CreateAdd(lhs, rhs, "add_tmp");
            case OpType::MINUS:
                return Builder->CreateSub(lhs, rhs, "sub_tmp");
            case OpType::STAR:
                return Builder->CreateMul(lhs, rhs, "mul_tmp");
            case OpType::DIV:
                return Builder->CreateSDiv(lhs, rhs, "div_tmp");
            case OpType::ASSIGNOP:
            {
                Value *lvalue = get_lvalue(now_F->getName().str(), lhs->getName().str());
                if (lvalue == nullptr)
                {
                    lvalue = lhs;
                }
                Builder->CreateStore(rhs, lvalue);
                return rhs;
            }
            case OpType::LT:
            {
                lhs = Builder->CreateICmpULT(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::GT:
            {
                lhs = Builder->CreateICmpUGT(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::LE:
            {
                lhs = Builder->CreateICmpULE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::GE:
            {
                lhs = Builder->CreateICmpUGE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::EQ:
            {
                lhs = Builder->CreateICmpEQ(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::NE:
            {
                lhs = Builder->CreateICmpNE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::AND:
            {
                lhs = Builder->CreateICmpNE(lhs, ConstantInt::get(context, APInt(32, 0)), "cmp_tmp");
                rhs = Builder->CreateICmpNE(rhs, ConstantInt::get(context, APInt(32, 0)), "cmp_tmp");
                lhs = Builder->CreateAnd(lhs, rhs, "and_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::OR:
            {
                lhs = Builder->CreateICmpNE(lhs, ConstantInt::get(context, APInt(32, 0)), "cmp_tmp");
                rhs = Builder->CreateICmpNE(rhs, ConstantInt::get(context, APInt(32, 0)), "cmp_tmp");
                lhs = Builder->CreateOr(lhs, rhs, "or_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            default:
                put_error("Unknown binary operator");
                break;
            }
        }
        else
        {
            switch (binary_exp->op)
            {
            case OpType::PLUS:
                return Builder->CreateFAdd(lhs, rhs, "add_tmp");
            case OpType::MINUS:
                return Builder->CreateFSub(lhs, rhs, "sub_tmp");
            case OpType::STAR:
                return Builder->CreateFMul(lhs, rhs, "mul_tmp");
            case OpType::DIV:
                return Builder->CreateFDiv(lhs, rhs, "div_tmp");
            case OpType::ASSIGNOP:
            {
                Value *lvalue = get_lvalue(now_F->getName().str(), lhs->getName().str());
                if (lvalue == nullptr)
                {
                    lvalue = lhs;
                }
                Builder->CreateStore(rhs, lvalue);
                return rhs;
            }
            case OpType::LT:
            {
                lhs = Builder->CreateFCmpULT(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::GT:
            {
                lhs = Builder->CreateFCmpUGT(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::LE:
            {
                lhs = Builder->CreateFCmpULE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::GE:
            {
                lhs = Builder->CreateFCmpUGE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::EQ:
            {
                lhs = Builder->CreateFCmpOEQ(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::NE:
            {
                lhs = Builder->CreateFCmpONE(lhs, rhs, "cmp_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::AND:
            {
                lhs = Builder->CreateFCmpONE(lhs, ConstantFP::get(context, APFloat(0.0)), "cmp_tmp");
                rhs = Builder->CreateFCmpONE(rhs, ConstantFP::get(context, APFloat(0.0)), "cmp_tmp");
                lhs = Builder->CreateAnd(lhs, rhs, "and_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            case OpType::OR:
            {
                lhs = Builder->CreateFCmpONE(lhs, ConstantFP::get(context, APFloat(0.0)), "cmp_tmp");
                rhs = Builder->CreateFCmpONE(rhs, ConstantFP::get(context, APFloat(0.0)), "cmp_tmp");
                lhs = Builder->CreateOr(lhs, rhs, "or_tmp");
                return Builder->CreateZExt(lhs, Type::getInt32Ty(context), "bool_tmp");
            }
            default:
                put_error("Unknown binary operator");
                break;
            }
        }

        break;
    }
    case NodeSubType::FuncCall:
    {
        auto func_call = (FuncCall *)node;
        Function *callee = TheModule->getFunction(func_call->name);
        if (callee == nullptr)
        {
            put_error("Unknown function referenced");
            return nullptr;
        }
        if (callee->arg_size() != func_call->args.size())
        {
            put_error("Incorrect # arguments passed");
            return nullptr;
        }
        std::vector<Value *> args;
        for (auto &arg : func_call->args)
        {
            auto arg_val = gen_Exp((Exp *)arg.get());
            if (arg_val->getType()->isPointerTy())
            {
                arg_val = Builder->CreateLoad(arg_val, "arg_tmp");
            }
            args.push_back(arg_val);
        }
        return Builder->CreateCall(callee, args, "call_tmp");
    }
    case NodeSubType::ArrayExp:
    {
        auto array_exp = (ArrayExp *)node;
        Value *array = gen_Exp((Exp *)array_exp->array.get());
        // 判断是否是指针
        if (!array->getType()->isPointerTy())
        {
            put_error("Array must be a pointer");
            return nullptr;
        }
        Value *index = gen_Exp((Exp *)array_exp->index.get());
        // 判断是否是指针
        if (index->getType()->isPointerTy())
        {
            index = Builder->CreateLoad(index, "index_tmp");
        }
        return Builder->CreateGEP(array, {ConstantInt::get(context, APInt(32, 0, true)), index}, "array_tmp");
    }
    }
    put_error("Unknown expression");
    return nullptr;
}

template <>
void CodeGen::code_gen<Dec>(Dec *node)
{
    assert(node != nullptr);
    auto var_dec = (VarDec *)node->var_dec.get();
    Type *type = get_type(node->spec_type);
    AllocaInst *Alloca = nullptr;
    if (var_dec->sub_type == NodeSubType::ElemDec)
    {
        // 单个变量
        Alloca = Builder->CreateAlloca(get_type(node->spec_type), nullptr, var_dec->name);
        NamedScopes[now_F->getName().str()][var_dec->name] = Alloca;
    }
    else
    {
        // 数组
        Alloca = Builder->CreateAlloca(gen_VarDec_Type(var_dec, get_type(node->spec_type)), nullptr, var_dec->name);
        NamedScopes[now_F->getName().str()][var_dec->name] = Alloca;
    }
    if (node->exp != nullptr)
    {
        // 有初始化
        Value *init = gen_Exp((Exp *)node->exp.get());
        if (init->getType()->isPointerTy())
        {
            init = Builder->CreateLoad(init, "init_tmp");
        }
        Builder->CreateStore(init, Alloca);
    }
    else
    {
        // 没有初始化的情况
        // 目前不支持数组初始化
        assert(var_dec->sub_type == NodeSubType::ElemDec);
        Builder->CreateStore(Constant::getNullValue(type), Alloca);
    }
    NamedScopes[now_F->getName().str()][var_dec->name] = Alloca;
}
template <>
void CodeGen::code_gen<Def>(Def *node)
{
    assert(node != nullptr);
    for (auto &dec : node->dec_list)
    {
        code_gen((Dec *)dec.get());
    }
}
template <>
void CodeGen::code_gen<ExpStmt>(ExpStmt *node)
{
    assert(node != nullptr);
    gen_Exp((Exp *)node->exp.get());
}
template <>
void CodeGen::code_gen<IfStmt>(IfStmt *node)
{
    assert(node != nullptr);
    Value *cond = gen_Exp((Exp *)node->cond.get());
    if (cond == nullptr)
    {
        put_error("If condition is not a boolean");
        return;
    }
    cond = Builder->CreateICmpNE(cond, ConstantInt::get(Type::getInt32Ty(context), 0), "ifcond");

    BasicBlock *ThenBB = BasicBlock::Create(context, "ifthen", now_F);
    BasicBlock *ElseBB = BasicBlock::Create(context, "ifelse");
    BasicBlock *MergeBB = BasicBlock::Create(context, "ifcont");

    Builder->CreateCondBr(cond, ThenBB, ElseBB);
    // 插入then块
    Builder->SetInsertPoint(ThenBB);
    // 产生then块的代码，没有返回值，不过当然可以写return
    code_gen((Stmt *)node->then_stmt.get());
    // 判断是否有return语句，如果没有，就插入br到merge块
    if (Builder->GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder->CreateBr(MergeBB);
    }
    // 更新then块
    ThenBB = Builder->GetInsertBlock();

    // 插入else块
    now_F->getBasicBlockList().push_back(ElseBB);
    Builder->SetInsertPoint(ElseBB);
    // 产生else块的代码
    if (node->else_stmt != nullptr)
    {
        code_gen((Stmt *)node->else_stmt.get());
    }
    // 判断是否有return语句，如果没有，就插入br到merge块
    if (Builder->GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder->CreateBr(MergeBB);
    }
    // 更新else块:并不需要，因为后面不会用到
    ElseBB = Builder->GetInsertBlock();
    // 插入merge块
    now_F->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);
}
template <>
void CodeGen::code_gen<WhileStmt>(WhileStmt *node)
{
    assert(node != nullptr);

    BasicBlock *CondBB = BasicBlock::Create(context, "whilecond", now_F);
    BasicBlock *BodyBB = BasicBlock::Create(context, "whilebody");
    BasicBlock *MergeBB = BasicBlock::Create(context, "whilecont");

    Builder->CreateBr(CondBB);

    Builder->SetInsertPoint(CondBB);
    // 产生条件
    Value *cond = gen_Exp((Exp *)node->cond.get());
    if (cond == nullptr)
    {
        put_error("While condition is not a boolean");
        return;
    }
    cond = Builder->CreateICmpNE(cond, ConstantInt::get(context, APInt(32, 0, true)), "whilecond");
    Builder->CreateCondBr(cond, BodyBB, MergeBB);

    now_F->getBasicBlockList().push_back(BodyBB);
    Builder->SetInsertPoint(BodyBB);
    // 产生循环体
    code_gen((Stmt *)node->body.get());
    if (Builder->GetInsertBlock()->getTerminator() == nullptr)
    {
        Builder->CreateBr(CondBB);
    }
    now_F->getBasicBlockList().push_back(MergeBB);
    Builder->SetInsertPoint(MergeBB);
}

Value *CodeGen::get_lvalue(std::string scope_name, std::string var_name)
{
    auto scope = NamedScopes.find(scope_name);
    if (scope == NamedScopes.end())
    {
        return nullptr;
    }
    auto var = scope->second.find(var_name);
    if (var == scope->second.end())
    {
        //在全局变量中找
        auto global_var = NamedScopes["global"].find(var_name);
        if (global_var == NamedScopes["global"].end())
        {
            return nullptr;
        }
        else
        {
            return global_var->second;
        }
    }
    return var->second;
}
template <>
void CodeGen::code_gen<ReturnStmt>(ReturnStmt *node)
{
    assert(node != nullptr);
    Value *ret = gen_Exp((Exp *)node->ret.get());
    Value *ret_ptr = get_lvalue(now_F->getName().str(), "return_ptr");
    // 判断ret是否是指针(左值)
    if (ret->getType()->isPointerTy())
    {
        ret = Builder->CreateLoad(ret);
    }
    Builder->CreateStore(ret, ret_ptr);
    // 创建br到return block
    Builder->CreateBr(now_return);
}
template <>
void CodeGen::code_gen<CompSt>(CompSt *node)
{
    assert(node != nullptr);
    assert(node->sub_type == NodeSubType::CompSt);
    for (auto &def : node->def_list)
    {
        code_gen((Def *)def.get());
    }
    for (auto &stmt : node->stmt_list)
    {
        code_gen((Stmt *)stmt.get());
    }
}
template <>
void CodeGen::code_gen<Stmt>(Stmt *node)
{
    assert(node != nullptr);
    assert(node->type == NodeType::Stmt);
    switch (node->sub_type)
    {
    case NodeSubType::CompSt:
        code_gen((CompSt *)node);
        break;
    case NodeSubType::ReturnStmt:
        code_gen((ReturnStmt *)node);
        break;
    case NodeSubType::ExpStmt:
        code_gen((ExpStmt *)node);
        break;
    case NodeSubType::IfStmt:
        code_gen((IfStmt *)node);
        break;
    case NodeSubType::WhileStmt:
        code_gen((WhileStmt *)node);
        break;
    }
}

template <>
void CodeGen::code_gen<ExtDef>(ExtDef *node)
{
    assert(node != nullptr);
    assert(node->type == NodeType::ExtDef);
    switch (node->sub_type)
    {
    case NodeSubType::FunDec:
        code_gen((FunDec *)node);
        break;
    case NodeSubType::ExtDecList:
        code_gen((ExtDecList *)node);
        break;
    default:
        put_error("not implemented");
        break;
    }
}
template <>
void CodeGen::code_gen<Program>(Program *node)
{
    assert(node != nullptr);
    assert(node->type == NodeType::Program);
    // 先将函数原型创建完成
    for (auto &ext_def : node->ExtDefList)
    {
        if (((ExtDef *)ext_def.get())->sub_type == NodeSubType::FunDec)
        {
            gen_ExtProtoType((FunDec *)ext_def.get());
        }
    }
    for (auto &ext_def : node->ExtDefList)
    {
        code_gen((ExtDef *)ext_def.get());
    }
}
template <class Node>
void CodeGen::code_gen(Node *node)
{
    assert(node != nullptr);
    put_error("not implemented");
}