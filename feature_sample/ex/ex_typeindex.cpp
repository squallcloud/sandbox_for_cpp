import ex;

#include <iostream>
#include <typeindex>

#define _PRINT(_id) ::printf("name = %s(%s) hash_code = %llx size = %llu \n", _id.name(), _id.raw_name(), _id.hash_code(), sizeof(_id))

namespace ex_typeindex {

class Hoge
{
public:
    int a{};
};

class Foo
{
public:
    int a{};
};

void Exec()
{
    auto&& hoge_id = typeid(Hoge);
    auto&& foo_id = typeid(Foo);

    _PRINT(hoge_id);
    _PRINT(foo_id);
}

}//ex_typeindex