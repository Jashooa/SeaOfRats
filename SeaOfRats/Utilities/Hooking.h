#pragma once

#include <Windows.h>

namespace Utilities
{
    namespace Hooking
    {
        //uintptr_t HookMethod(uintptr_t virtualMethod, uintptr_t hookMethod);
        void* VMTHook(void* virtualTable, size_t offset, void* hookMethod);
        void* IATHook(const char* targetDll, const char* targetFunction, void* hookMethod);
    }
}
