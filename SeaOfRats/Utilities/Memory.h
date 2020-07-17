#pragma once

#include <Windows.h>

namespace Utilities
{
    uintptr_t FindPattern(const uintptr_t start, const size_t length, const unsigned char* pattern, const char* mask);
}
