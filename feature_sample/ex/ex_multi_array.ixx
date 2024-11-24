export module ex_multi_array;

import dummy;
import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_multi_array {

void Exec()
{
    int hoge[(10, 20)]{};

    const int foo = _countof(hoge);
    const int piyo = sizeof(hoge) / sizeof(int);

    ::printf("x = %d, y = %d \n", foo, piyo);

    for (int idx0 = 0; idx0 < 10; idx0++) {
        for (int idx1 = 0; idx1 < 20; idx1++) {
            const auto val = hoge[(idx0, idx1)];
            ::printf("[%d, %d] = %d \n", idx0, idx1, val);
        }
    }
}

}//ex_multi_array