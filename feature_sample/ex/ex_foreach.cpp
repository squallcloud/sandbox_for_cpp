module ex_foreach;

import dummy;

namespace ex_foreach {

void Exec()
{
    ex::Dummy dmy_array[10] { 1, };

    // foreach 各要素を参照でとれる
    for (auto& dmy : dmy_array) {
        dmy.value = 10;
    }
}

}//ex_foreach