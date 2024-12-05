import ex;

#include <iostream>

namespace ex_lamda {

class Hoge
{
public:
    void Func() {
        const auto func = [this]() {
            ::printf("%s %d %f %d %d \n", __FUNCSIG__, hoge, foo, piyo, hogehoge);
        };

        func();

        ::printf("address = %p  size = %llu \n", &func, sizeof(func));
    }

private:
    int hoge = 100;
    float foo = 100.0f;
    short piyo = 10;
    char hogehoge = 1;
};

void Exec()
{
    {
        int hoge = 100;
        float foo = 100.0f;
        short piyo = 10;
        char hogehoge = 1;

        const auto func = [&]() {
            ::printf("%s %d %f %d %d \n", __FUNCSIG__, hoge, foo, piyo, hogehoge);
        };

        const auto func2 = [hoge, foo, piyo, hogehoge]() {
            ::printf("%s %d %f %d %d \n", __FUNCSIG__, hoge, foo, piyo, hogehoge);
        };

        func();
        func2();

        ::printf("address = %p  size = %llu \n", &func, sizeof(func));
        ::printf("address = %p  size = %llu \n", &func2, sizeof(func2));
    }

    {
        Hoge hoge;
        hoge.Func();
    }
}

}//ex_lamda