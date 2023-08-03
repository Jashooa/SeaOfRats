#include "Memory.h"

#include <Psapi.h>

#include <cstdint>
#include <cstring>

namespace Utilities
{
	// Change to a function that takes just the pattern without mask
	// Add overrides for automatically finding module address and length from name
	uintptr_t FindPattern(uintptr_t start, size_t length, const unsigned char* pattern, const char* mask)
	{
		size_t pos = 0;
		const auto maskLength = std::strlen(mask) - 1;

		const auto moduleLength = start + length;
		for (size_t it = start; it < moduleLength; ++it)
		{
			if (*reinterpret_cast<unsigned char*>(it) == pattern[pos] || mask[pos] == '?')
			{
				if (mask[pos + 1] == '\0')
				{
					return it - maskLength;
				}

				pos++;
			}
			else
			{
				pos = 0;
			}
		}

		return 0;
	}

	uintptr_t GetAbsoluteAddress(uintptr_t address, uint32_t rva_offset, uint32_t rip_offset)
	{
		uint32_t rva = *reinterpret_cast<uint32_t*>(address + rva_offset);
		return address + rva + rip_offset;
	}
}
