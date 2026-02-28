#pragma once
#include "ex002_auto_init/auto_init.h"

namespace ex002_auto_init {

// --- メイン関数 ---
int main()
{

    {
        // 関数があるクラス
        class HasPost {
        public:
            HasPost() {
                printf("HasPost born.\n");
            }
            void post_construct() {
                printf("HasPost::post_construct() called!\n");
            }
        };

        class NoPost
        {
        public:
            NoPost(int v) {
                printf("NoPost born with %d.\n", v);
            }
        };

        AutoInit<HasPost> obj1;
        AutoInit<NoPost> obj2(42);
    }

    return 0;
}

}//ex002_auto_init