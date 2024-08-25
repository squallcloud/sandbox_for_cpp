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

int main(void)
{
#define __DEF_INFO(name) #name, &name::Exec,
    std::unordered_map<std::string, std::function<void()>> s_func_list {
        { __DEF_INFO(ex_foreach) },
        { __DEF_INFO(ex_tuple) },
        { __DEF_INFO(ex_initializer_lists) },
        { __DEF_INFO(ex_thread) },
        { __DEF_INFO(ex_field_init) },
        { __DEF_INFO(ex_multi_array) },
    };
#undef __DEF_INFO

    for (auto& func_info : s_func_list) {
        const auto& mod_name = func_info.first;
        const auto& func = func_info.second;

        ex::Dummy::ResetCounter();
        ::printf("[%s] \n", mod_name.c_str());
        func();
        ::printf("\n");
    }

    return 0;
}