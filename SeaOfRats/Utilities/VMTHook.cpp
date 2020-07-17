#include <Windows.h>

#include "VMTHook.h"

namespace Utilities
{
	/*uintptr_t HookMethod(uintptr_t virtualTable, uintptr_t hookMethod, size_t offset)
	{
		uintptr_t vTable = *reinterpret_cast<uintptr_t*>(virtualTable);
		uintptr_t entry = vTable + (offset * sizeof(uintptr_t));
		uintptr_t orig = *reinterpret_cast<uintptr_t*>(entry);

		DWORD oldProtection;
		::VirtualProtect(reinterpret_cast<LPVOID>(entry), sizeof(entry), PAGE_EXECUTE_READWRITE, &oldProtection);

		*reinterpret_cast<uintptr_t*>(entry) = hookMethod;

		::VirtualProtect(reinterpret_cast<LPVOID>(entry), sizeof(entry), oldProtection, &oldProtection);

		return orig;
	}*/

	void* HookMethod(void* virtualTable, size_t offset, void* hookMethod)
	{
		uintptr_t vTable = reinterpret_cast<uintptr_t>(virtualTable);
		uintptr_t entry = vTable + (offset * sizeof(uintptr_t));
		uintptr_t orig = *reinterpret_cast<uintptr_t*>(entry);

		DWORD oldProtection;
		::VirtualProtect(reinterpret_cast<LPVOID>(entry), sizeof(entry), PAGE_EXECUTE_READWRITE, &oldProtection);

		*reinterpret_cast<uintptr_t*>(entry) = reinterpret_cast<uintptr_t>(hookMethod);

		::VirtualProtect(reinterpret_cast<LPVOID>(entry), sizeof(entry), oldProtection, &oldProtection);

		return reinterpret_cast<void*>(orig);
	}
}
