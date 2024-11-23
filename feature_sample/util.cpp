import util;

#include <chrono>
#include <functional>

namespace ex::util {

// 速度計測用関数
duration_type profile_func(const std::function<void()>&& in_callback)
{
    const time_point_type point1 = ns_clock::now();

    in_callback();

    const time_point_type point2 = ns_clock::now();

    const duration_type dis = point2 - point1;
    return dis;
}

}//ex::util