#pragma once

#include <Windows.h>

#include <cstdint>

namespace Utilities
{
    uintptr_t FindPattern(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask);
    uintptr_t GetAbsoluteAddress(uintptr_t address, uint32_t rva_offset, uint32_t rip_offset);
}
