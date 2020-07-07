#pragma once
#include <Windows.h>

namespace Utilities
{
    //uintptr_t HookMethod(uintptr_t virtualMethod, uintptr_t hookMethod);
    void* HookMethod(void* virtualTable, size_t offset, void* hookMethod);
}
