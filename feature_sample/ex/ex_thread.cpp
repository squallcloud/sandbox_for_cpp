import ex;

import dummy;
#include <thread>
#include <chrono>

namespace ex_thread {

void Exec()
{
    int x{};
    int y{};

    std::thread t([&] {
        for (int idx = 0; idx < 1000; idx++) {
            ++x;
            ::printf("x = %d \n", x);
        }
    });

    std::this_thread::sleep_for(std::chrono::microseconds(16));

    --y;
    ::printf("y = %d \n", y);

    t.join();
}

}//ex_thread