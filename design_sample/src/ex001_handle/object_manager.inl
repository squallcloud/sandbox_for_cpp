#pragma once

#include "ex001_handle/object_manager.h"

namespace ex001_handle {

ObjectManager::ObjectManager()
{
    slots_.reserve(16);
    printf("MyObjectManager が初期化されました。 \n");
}

ObjectManager::~ObjectManager()
{
    printf("MyObjectManager が破棄されました。 \n");
}

ObjectHandle ObjectManager::CreateObject(int32_t init_val)
{
    uint16_t index{};

    if (!free_indices_.empty()) {
        index = free_indices_.back();
        free_indices_.pop_back();
        // 既存のスロットを再利用する場合、バージョンをインクリメント
        slots_[index].version++;
        slots_[index].object = Object{ init_val }; // Placement new を使う場合は注意
    } else {
        index = static_cast<decltype(index)>(slots_.size());

        // 新しいスロットにオブジェクトを構築
        slots_.emplace_back(
            Object{ init_val },
            (uint16_t)0,
            true
        );
    }

    slots_[index].is_used = true;

    printf("  オブジェクト作成: インデックス=%u, バージョン=%u \n", index, slots_[index].version);

    return ObjectHandle{ { index, slots_[index].version } };
}

// オブジェクトを破棄
void ObjectManager::DestroyObject(ObjectHandle handle)
{
    if (!isValidHandle(handle)) {
        printf("  エラー: 既に無効か不正なハンドルを破棄しようとしました。 \n");
        return;
    }

    ObjectSlot& slot = slots_[handle.handle_data_.index];
    if (slot.version != handle.handle_data_.version) {
        // バージョン不一致（既に再利用されたスロットの古いハンドル）
        printf("  エラー: 古いバージョンのハンドルでオブジェクトを破棄しようとしました。 \n");
        return;
    }

    std::cout << "  オブジェクト破棄: インデックス=" << handle.handle_data_.index << ", バージョン=" << slot.version << "\n";
    slot.object.~Object(); // オブジェクトのデストラクタを手動で呼び出す（非推奨：POD以外は注意）
    // std::vector::erase()を使うか、placement new の逆を行う
    slot.is_used = false;
    // バージョンをインクリメントしてからフリーリストに追加（次にこのスロットが使われた時用）
    slot.version++;
    free_indices_.push_back(handle.handle_data_.index);
}

bool ObjectManager::isValidHandle(ObjectHandle handle) const
{
    if (handle.handle_data_.index >= slots_.size() || !slots_[handle.handle_data_.index].is_used) {
        return false; // インデックスが範囲外か、スロットが使用中でない
    }
    // バージョンが一致しない場合も無効
    return slots_[handle.handle_data_.index].version == handle.handle_data_.version;
}

Object* ObjectManager::GetObjectPtr(ObjectHandle handle)
{
    if (!isValidHandle(handle)) {
        return nullptr;
    }

    return &slots_[handle.handle_data_.index].object;
}

const Object* ObjectManager::GetObjectPtr(ObjectHandle handle) const
{
    if (!isValidHandle(handle)) {
        return nullptr;
    }

    return &slots_[handle.handle_data_.index].object;
}

}//ex001_handle