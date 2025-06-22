#pragma once

namespace ex001_handle {

/*
ハンドルが内部に持つ情報
これをハンドルクラスのfriendにするか、publicにするかは設計による
*/
struct HandleData final
{
    uint16_t index;// マネージャーの配列内のインデックス
    uint16_t version; // オブジェクトが再利用されたかチェックするためのバージョン

    bool operator==(const HandleData& other_data) const {
        return index == other_data.index && version == other_data.version;
    }
};

/*
ハンドルクラス
*/
class ObjectHandle
{
public:
    ObjectHandle();
    ObjectHandle(HandleData&& handle_data);

    //ハンドルが有効かどうかをチェック
    bool IsValid() const;

    Object& operator*();
    const Object& operator*() const;
    Object* operator->();
    const Object* operator->() const;
    bool operator==(const ObjectHandle& other_handle) const;
    bool operator!=(const ObjectHandle& other_handle) const;



    HandleData handle_data_{};
};

}//ex001_handle