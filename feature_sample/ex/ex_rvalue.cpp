import ex_rvalue;

import dummy;
#include <iostream>
#include <compare>
#include <tuple>
#include <string>

namespace ex_rvalue {

class Hoge
{
public:
    Hoge() {
        ::printf("%s \n", __FUNCSIG__);
    }

    Hoge(Hoge&& in_rhs)
    : dummy(std::move(in_rhs.dummy))
    {
        ::printf("%s \n", __FUNCSIG__);
    }

    void Exec() {
        ::printf("%s \n", __FUNCSIG__);
    }

    void Exec() const {
        ::printf("%s \n", __FUNCSIG__);
    }

    int operator()() {
        ::printf("%s \n", __FUNCSIG__);
        return 0;
    }

    int operator()() const {
        ::printf("%s \n", __FUNCSIG__);
        return 0;
    }

private:
    ex::Dummy dummy;
};

void Exec()
{
    const auto&& hoge = Hoge();
    const auto hoge2(std::move(Hoge()));
    const Hoge hoge3 = Hoge();
    const Hoge&& hoge4 = Hoge();

    hoge.Exec();
    hoge2.Exec();
    hoge3.Exec();
    hoge4.Exec();

    auto hoge5 = Hoge()();
    auto hoge6 = hoge4();
    auto&& hoge7 = hoge4;
}

}//ex_rvalue