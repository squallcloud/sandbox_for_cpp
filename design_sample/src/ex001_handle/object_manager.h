#pragma once

#include "object_handle.h"

namespace ex001_handle {

/*
マネージャークラス
*/
class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    // オブジェクトを生成し、ハンドルを返す
    ObjectHandle CreateObject(int32_t init_val);

    // オブジェクトを破棄
    void DestroyObject(ObjectHandle handle);

    // ハンドルが有効かつ、指しているオブジェクトが現在有効かをチェック
    bool isValidHandle(ObjectHandle handle) const;

    /*
    ハンドルから実際のオブジェクトへのポインタを取得
    (MyObjectHandle クラスからのみアクセスされることを想定)
    */
    Object* GetObjectPtr(ObjectHandle handle);
    const Object* GetObjectPtr(ObjectHandle handle) const;



private:
    // オブジェクトの格納スロット
    struct ObjectSlot
    {
        Object object{ 0 };//実際のオブジェクト
        uint16_t version{};//このスロットの現在のバージョン
        bool is_used{};// このスロットが現在使用中か
    };

    /*
    グローバルなIDカウンタ（バージョンを含まない純粋なID管理にも使えるが、今回はバージョンで代用）
     uint32_t m_nextId = 1; // 0を無効なハンドルIDとすることも多い
    */
    using SlotsType = std::vector<ObjectSlot>;
    using FreeIndicesType = std::vector<uint16_t>;

    SlotsType slots_;//スロット
    FreeIndicesType free_indices_;//空いているスロットのインデックス
};

inline ObjectManager* g_object_manager{};//ObjectManagerの実体

}//ex001_handle