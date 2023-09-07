export module dummy;

import <iostream>;
import <mutex>;

export namespace ex {

class Dummy
{
    static uint64_t s_instance_counter;
    static std::mutex s_mutex;

public:
    Dummy() {
        UpdateCounter(serial_id);
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(const Dummy& in_rhs) {
        UpdateCounter(serial_id);
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(Dummy&& in_rhs) {
        UpdateCounter(serial_id);
        ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    }

    Dummy(const uint64_t in_val) {
        UpdateCounter(serial_id);
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

protected:
    static void UpdateCounter(uint64_t& ref_serial_id) {
        std::lock_guard<std::mutex> lock(s_mutex);
        ref_serial_id = s_instance_counter;
        s_instance_counter++;
    }


public:
    uint64_t serial_id{};
    uint64_t value{};
};

//static
uint64_t Dummy::s_instance_counter{};

//static
std::mutex Dummy::s_mutex{};

}//ex