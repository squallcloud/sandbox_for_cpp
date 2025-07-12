#pragma once

namespace ex001_handle {

/*
管理されるオブジェクトの定義
*/
struct Object final
{
    int32_t value;


    Object(const int in_val);
    ~Object();
    void Print() const;
};

}//ex001_handle