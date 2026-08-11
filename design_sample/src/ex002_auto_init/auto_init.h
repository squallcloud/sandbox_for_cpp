#pragma once

namespace ex002_auto_init {

// Tに post_construct() が生えている時だけ実行するラッパークラス
template <typename T>
class AutoInit : public T
{
public:
    template <typename... Args>
    AutoInit(Args&&... args)
    : T(std::forward<Args>(args)...)
    {
        /*
        t.post_construct()
        t.PostConstruct()
        が呼び出し可能(有効な式)かどうかをコンパイル時に判定

        存在する場合のみコンパイル・実行される
        */
        if constexpr (requires(T t) { t.post_construct(); }) {
            this->post_construct();
        }
        if constexpr (requires(T t) { t.PostConstruct(); }) {
            this->PostConstruct();
        }
    }
};

}//ex002_auto_init