#include <functional>
#include <string>
#include <map>
import dummy;
import ex;

int main(void)
{
    struct FuncInfo {
        std::string str{};
        std::function<void()> func{};
    };

    const FuncInfo s_func_list[] {
    #define DEFINE_EXPORT_EX(name) { #name, &name::Exec, },
    #include "ex.h"
    #undef DEFINE_EXPORT_EX
    };

    for (auto& func_info : s_func_list) {
        const auto& mod_name = func_info.str;
        const auto& func = func_info.func;

        ex::Dummy::ResetCounter();
        ::printf("[%s] \n", mod_name.c_str());
        func();
        ::printf("\n");
    }

    return 0;
}