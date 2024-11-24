import ex;

import dummy;
#include <variant>

namespace ex_variant {

void Exec()
{
    std::variant<ex::Dummy, int, short> var;
    var = 10;

    ::printf("index = %llu \n", var.index());

    var = ex::Dummy();

    ::printf("index = %llu \n", var.index());

    var = (short)10;

    ::printf("index = %llu \n", var.index());

    ::printf("var size = %llu \n", sizeof(var));
}

}//ex_variant