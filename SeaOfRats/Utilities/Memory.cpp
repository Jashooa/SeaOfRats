#include "Memory.h"

#include <Psapi.h>
#include <Windows.h>

#include <cstring>

namespace Utilities
{
	/*bool CompareByteArray(const unsigned char* data, const unsigned char* pattern)
	{
		for (; *pattern; ++pattern, ++data)
		{
			if (*data == '\x00')
			{
				continue;
			}
			if (*data != *pattern)
			{
				return false;
			}
		}

		return true;
	}

	uintptr_t FindPattern(const uintptr_t start, const size_t length, const unsigned char* pattern)
	{
		const auto first = pattern[0];
		const auto patternLength = std::strlen(reinterpret_cast<const char*>(pattern));
		const auto max = start + length - patternLength;

		for (auto it = start; it < max; ++it)
		{
			if (*reinterpret_cast<unsigned char*>(it) != first)
			{
				continue;
			}
			if (CompareByteArray(reinterpret_cast<unsigned char*>(it), pattern))
			{
				return it;
			}
		}

		return 0;
	}

	bool DataCompare(unsigned char* data, unsigned char* pattern, char* mask)
	{
		for (; *mask; ++mask, ++data, ++pattern)
		{
			if (*mask == 'x' && *data != *pattern)
			{
				return false;
			}
		}

		return *mask == NULL;
	}

	uintptr_t FindPattern(const uintptr_t start, const size_t length, unsigned char* pattern, char* mask)
	{
		const auto max = length - std::strlen(mask);

		for (auto i = 0; i < max; ++i)
		{
			if (DataCompare(reinterpret_cast<unsigned char*>(start + i), pattern, mask))
			{
				return start + i;
			}
		}

		return 0;
	}*/

	uintptr_t FindPattern(const uintptr_t start, const size_t length, const unsigned char* pattern, const char* mask)
	{
		size_t pos = 0;
		const auto maskLength = std::strlen(mask) - 1;

		//uintptr_t tmpAddress = 0;
		const auto moduleLength = start + length;
		for (auto it = start; it < moduleLength; ++it)
		{
			if (*reinterpret_cast<unsigned char*>(it) == pattern[pos] || mask[pos] == '?')
			{
				if (mask[pos + 1] == '\0')
				{
					return it - maskLength;
				}
				/*if (tmpAddress == 0)
				{
					tmpAddress = it;
				}*/
				pos++;
			}
			else
			{
				/*if (tmpAddress > 0)
				{
					it = tmpAddress;
					tmpAddress = 0;
				}*/
				pos = 0;
			}
		}

		return 0;
	}
}
