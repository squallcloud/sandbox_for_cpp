export module ex_defined_macro;

import dummy;
import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_defined_macro {

class Hoge
{
public:
    Hoge() {
        ::printf("__FUNCSIG__  > %s \n", __FUNCSIG__);
    }

    void Func() {
        ::printf("__FUNCSIG__  > %s \n", __FUNCSIG__);
    }

    void Func() const {
        ::printf("__FUNCSIG__  > %s \n", __FUNCSIG__);
        ::printf("__FUNCTION__ > %s \n", __FUNCTION__);
    }
};

void Exec()
{
    ::printf("__DATE__ > %s \n", __DATE__);
    ::printf("__FILE__ > %s \n", __FILE__);
    ::printf("__LINE__ > %d \n", __LINE__);
    ::printf("__TIME__ > %s \n", __TIME__);
    ::printf("__func__ > %s \n", __func__);
    ::printf("__FUNCTION__ > %s \n", __FUNCTION__);
    ::printf("__TIMESTAMP__ > %s \n", __TIMESTAMP__);

    Hoge hoge;
    hoge.Func();

    const Hoge hoge_const;
    hoge_const.Func();
}

}//ex_defined_macro