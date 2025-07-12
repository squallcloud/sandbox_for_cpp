#pragma once

#include "ex001_handle/object.h"

namespace ex001_handle {

Object::Object(const int in_val)
: value(in_val)
{
    ::printf("Object(%d) が構築されました。 \n", value);
}

Object::~Object()
{
    ::printf("Object(%d) が破棄されました。 \n", value);
}

void Object::Print() const
{
    ::printf("  Object の値: %d \n", value);
}

}//ex001_handle