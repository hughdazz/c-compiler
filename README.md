# c-compiler

这是使用cpp编写的类c语法的中间代码生成器，可以将类c语法的代码转换为LLVM IR，并通过LLVM的JIT编译器进行编译运行。

## 1 依赖

cJSON库:已作为源文件cJSON.c和cJSON.h包含在deps目录中
LLVM库:需要安装最新版本到本地环境中
flex:需要安装最新版本到本地环境中
bison:需要安装最新版本到本地环境中
GCC or clang:需要支持std=c11及以上标准

## 2 编译

确保项目根目录有build目录，然后执行以下命令
```bash
make
```
需要其他编译选项请自行修改Makefile文件

## 3 运行

```bash
./build/c-compiler
```

## 4 项目结构

```
/src
    /ast
        ast.h
    /codegen
        codegen.cpp
        codegen.h
    /parser
        lex.l
        yacc.y
        parse.cpp
        parse_def.h
    /JIT
        jit.cpp
        jit.h
    main.cpp
```