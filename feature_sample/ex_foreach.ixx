export module ex_foreach;

import <iostream>;

export namespace ex_foreach {

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

void Exec()
{
    Dummy dmy_array[10] { 1, };

    // foreach 各要素を参照でとれる
    for (auto& dmy : dmy_array) {
        dmy.value = 10;
    }
}

}//ex_foreach