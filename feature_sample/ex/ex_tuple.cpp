import ex;

import dummy;
#include <iostream>
#include <compare>
#include <tuple>
#include <string>

namespace ex_tuple {

// 関数から複数の値を返す
std::tuple<int, char, ex::Dummy> f()
{
    // std::make_tuple()はほとんどの状況で必要ない
    return { 1, 'a', 20, };
}

void Exec()
{
    // 構造化束縛でタプルを分解して、それぞれの要素を代入
    auto [a, b, c] = f();//ここでコピーは走らない

    std::tuple<int, char, ex::Dummy> t = std::make_tuple(1, 'a', 1);//コピーは走らない

    auto s = std::get<2>(t);//&つけないとコピーが走る
    auto& ref_s = std::get<2>(t);
    auto&& rref_s = std::get<2>(t);
}

}//ex_tuple