export module ex_initializer_lists;

import dummy;
import <vector>;

export namespace ex_initializer_lists {

template <class T>
class MyVector
{
public:
    // リスト初期化用のコンストラクタ
    MyVector(std::initializer_list<T> init)
    : data_(init.begin(), init.end())
    {
    }


private:
    std::vector<T> data_;
};

void Exec()
{
    MyVector<ex::Dummy> v = { 1, 2, 3 };
}

}//ex_initializer_lists