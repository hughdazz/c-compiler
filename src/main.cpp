#include <iostream>
#include "parser/parse_def.h"
#include "code_gen/code_gen.h"
Module *TheModule;
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
    // parse("int main(){}", &tree);
    // std::cout << cJSON_Print(tree) << std::endl;
    // parse("int sum(int a,int b)\n{return 1+a;}", &tree);
    // parse("int main(int a,int b){}", &tree);
    // std::cout << cJSON_Print(tree) << std::endl;
    parse("9+3*2", &tree);
    std::cout << cJSON_Print(tree) << std::endl;
    code = visitor<NodeType::Exp>::code_gen(tree);
    std::cout << code;
    std::cout << std::endl;

    return 0;
}