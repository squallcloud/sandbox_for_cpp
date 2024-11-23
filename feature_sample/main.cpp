#include <functional>
#include <string>
#include <map>
import <iostream>;
import dummy;
import ex_foreach;
import ex_tuple;
import ex_initializer_lists;
import ex_thread;
import ex_field_init;
import ex_multi_array;
import ex_template_meta_program;
import ex_defined_macro;
import ex_rvalue;
import ex_component_oriented;

int main(void)
{
    struct FuncInfo {
        std::string str{};
        std::function<void()> func{};
    };

#define __DEF_INFO(name) #name, &name::Exec,
    const FuncInfo s_func_list[] {
        { __DEF_INFO(ex_foreach) },
        { __DEF_INFO(ex_tuple) },
        { __DEF_INFO(ex_initializer_lists) },
        { __DEF_INFO(ex_thread) },
        { __DEF_INFO(ex_field_init) },
        { __DEF_INFO(ex_multi_array) },
        { __DEF_INFO(ex_template_meta_program) },
        { __DEF_INFO(ex_defined_macro) },
        { __DEF_INFO(ex_rvalue) },
        { __DEF_INFO(ex_component_oriented) },
    };
#undef __DEF_INFO

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