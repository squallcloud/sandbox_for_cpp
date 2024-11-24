export module ex_field_init;

import dummy;
import <iostream>;
import <compare>;
import <tuple>;
import <string>;

export namespace ex_field_init {

void Exec()
{
    {//指示付き初期化
        struct Hoge {
            int x{};
            int y{};
        };

        // 変数指定で初期化できる
        Hoge hoge{
            .x = 1,
            .y = 2,
        };

        ::printf("x = %d, y = %d \n", hoge.x, hoge.y);
    }

    {
        struct Hoge {
            int x : 16 = 2;
            int y : 16{4};
        };

        Hoge hoge{};

        ::printf("x = %d, y = %d \n", hoge.x, hoge.y);
    }

    {
        struct Hoge {
            const int x{};
            const int y{};
        };

        Hoge hoge{
            .x = 5,
            .y = 4,
        };

        ::printf("x = %d, y = %d \n", hoge.x, hoge.y);
    }
}

}//ex_field_init