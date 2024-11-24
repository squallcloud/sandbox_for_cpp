import dummy;

#include <iostream>

namespace ex {

//static
void Dummy::ResetCounter()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    s_instance_counter = 0;
}

Dummy::Dummy()
{
    UpdateCounter(serial_id);
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
}

Dummy::Dummy(const Dummy& in_rhs)
{
    UpdateCounter(serial_id);
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
}

Dummy::Dummy(Dummy&& in_rhs)
{
    UpdateCounter(serial_id);
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
}

Dummy::Dummy(const uint64_t in_val)
{
    UpdateCounter(serial_id);
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);

    value = in_val;
}

Dummy::~Dummy()
{
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
}

Dummy& Dummy::operator=(const Dummy& in_rhs)
{
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    return *this;
}

Dummy& Dummy::operator=(Dummy&& in_rhs)
{
    ::printf("%s[%llu] \n", __FUNCSIG__, serial_id);
    return *this;
}

//static
void Dummy::UpdateCounter(uint64_t& ref_serial_id)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    ref_serial_id = s_instance_counter;
    s_instance_counter++;
}

}//ex