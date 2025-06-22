#pragma once

#include "ex001_handle/object_handle.h"
#include "ex001_handle/object_manager.h"

namespace ex001_handle {

ObjectHandle::ObjectHandle()
{
}

ObjectHandle::ObjectHandle(HandleData&& handle_data)
: handle_data_(handle_data)
{
}

// ハンドルが有効かどうかをチェック
bool ObjectHandle::IsValid() const {
    if (g_object_manager == nullptr) {
        return false;
    }

    return g_object_manager->isValidHandle(handle_data_);
}

Object& ObjectHandle::operator*()
{
    if (!IsValid()) {
        throw std::runtime_error("無効なハンドルをデリファレンスしようとしました！");
    }

    return *g_object_manager->GetObjectPtr(handle_data_);
}

const Object& ObjectHandle::operator*() const
{
    if (!IsValid()) {
        throw std::runtime_error("無効なハンドルをデリファレンスしようとしました！");
    }

    return *g_object_manager->GetObjectPtr(handle_data_);
}

Object* ObjectHandle::operator->()
{
    if (!IsValid()) {
        throw std::runtime_error("無効なハンドルに対してメンバアクセスしようとしました！");
    }

    return g_object_manager->GetObjectPtr(handle_data_);
}

const Object* ObjectHandle::operator->() const
{
    if (!IsValid()) {
        throw std::runtime_error("無効なハンドルに対してメンバアクセスしようとしました！");
    }

    return g_object_manager->GetObjectPtr(handle_data_);
}

bool ObjectHandle::operator==(const ObjectHandle& other_handle) const
{
    return handle_data_ == other_handle.handle_data_;
}

bool ObjectHandle::operator!=(const ObjectHandle& other_handle) const
{
    return !operator==(other_handle);
}

}//ex001_handle