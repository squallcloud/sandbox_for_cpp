#include "pch.h"

#include "ex001_handle/ex.inl"
#include "ex002_auto_init/ex.inl"

int main()
{
    ::printf("Hello, World!\n");

    ex001_handle::main();
    ex002_auto_init::main();

    return 0;
}
