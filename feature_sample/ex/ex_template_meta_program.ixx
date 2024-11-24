export module ex_template_meta_program;

import dummy;
import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_template_meta_program {

// check divisibility
template <int u, int v>
struct Divisible
{
    enum { value = u % v == 0 ? 1 : 0 };
};

// check divide by zero condition
template <int u>
struct Divisible<u, 0>
{
    enum { value = -1 };
};

void Exec()
{
    //TODO:
    const int hoge = Divisible<10, 0>::value;
}

}//ex_template_meta_program