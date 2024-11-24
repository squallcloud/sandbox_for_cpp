export module dummy;

import <mutex>;

export namespace ex {

class Dummy
{
    inline static uint64_t s_instance_counter{};
    inline static std::mutex s_mutex{};

public:
    static void ResetCounter();

    Dummy();
    Dummy(const Dummy& in_rhs);
    Dummy(Dummy&& in_rhs);
    Dummy(const uint64_t in_val);

    ~Dummy();

    Dummy& operator=(const Dummy& in_rhs);
    Dummy& operator=(Dummy&& in_rhs);

protected:
    static void UpdateCounter(uint64_t& ref_serial_id);


public:
    uint64_t serial_id{};
    uint64_t value{};
};

}//ex