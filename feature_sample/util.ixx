export module util;

import <chrono>;
import <functional>;

export namespace ex::util {

using ns_clock = std::chrono::system_clock;
using time_point_type = ns_clock::time_point;
using duration_type = ns_clock::duration;

duration_type profile_func(const std::function<void()>&& in_callback);

}//ex::util