import ex;

import dummy;
#include <vector>

namespace ex_initializer_lists {

template <class T>
class MyVector
{
public:
    // リスト初期化用のコンストラクタ
    MyVector(std::initializer_list<T> init)
    : data_(init.begin(), init.end())
    {
        ::printf("%s \n", __FUNCSIG__);
    }


private:
    std::vector<T> data_;
};

void Exec()
{
    MyVector<ex::Dummy> v1 = { 1, 2, 3 };
    MyVector<ex::Dummy> v2 { 1, 2, 3 };

    std::initializer_list<ex::Dummy> init_list {
        10, 20, 30,
    };

    MyVector<ex::Dummy> v3(init_list);
    MyVector<ex::Dummy> v4 = init_list;
}

}//ex_initializer_lists