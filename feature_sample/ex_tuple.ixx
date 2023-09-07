export module ex_tuple;

import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_tuple {

class Dummy
{
    static uint64_t s_instance_counter;

public:
    Dummy() {
        serial_id = s_instance_counter;
        s_instance_counter++;
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(const Dummy& in_rhs) {
        serial_id = s_instance_counter;
        s_instance_counter++;
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(Dummy&& in_rhs) {
        serial_id = s_instance_counter;
        s_instance_counter++;
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(const uint64_t in_val) {
        serial_id = s_instance_counter;
        s_instance_counter++;
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);

        value = in_val;
    }

    ~Dummy() {
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy& operator=(const Dummy& in_rhs) {
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
        return *this;
    }

    Dummy& operator=(Dummy&& in_rhs) {
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
        return *this;
    }

public:
    uint64_t serial_id{};
    uint64_t value{};
};

//static
uint64_t Dummy::s_instance_counter = 0;


// 関数から複数の値を返す
std::tuple<int, char, Dummy> f()
{
    // std::make_tuple()はほとんどの状況で必要ない
    return { 1, 'a', 20, };
}

void Exec()
{
    // 構造化束縛でタプルを分解して、それぞれの要素を代入
    auto [a, b, c] = f();//ここでコピーは走らない

    std::tuple<int, char, Dummy> t = std::make_tuple(1, 'a', 1);//コピーは走らない

    auto s = std::get<2>(t);//&つけないとコピーが走る
    auto& ref_s = std::get<2>(t);
    auto&& rref_s = std::get<2>(t);
}

}//ex_tuple