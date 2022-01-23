#include <Windows.h>

#include <string>

#include "Hooking.h"

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

	void* VMTHook(void* virtualTable, size_t offset, void* hookMethod)
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

	void* IATHook(const char* targetDll, const char* targetFunction, void* hookMethod)
	{
		HMODULE imageBase = GetModuleHandleA(NULL);

		if (!imageBase)
		{
			return NULL;
		}

		PIMAGE_DOS_HEADER dosHeaders = reinterpret_cast<PIMAGE_DOS_HEADER>(imageBase);
		PIMAGE_NT_HEADERS ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD_PTR>(imageBase) + dosHeaders->e_lfanew);
		IMAGE_DATA_DIRECTORY importsDirectory = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
		PIMAGE_IMPORT_DESCRIPTOR importDescriptor = reinterpret_cast<PIMAGE_IMPORT_DESCRIPTOR>(reinterpret_cast<DWORD_PTR>(imageBase) + importsDirectory.VirtualAddress);

		LPCSTR libraryName = NULL;
		PIMAGE_IMPORT_BY_NAME functionName = NULL;

		while (importDescriptor->Characteristics)
		{
			libraryName = reinterpret_cast<LPCSTR>(reinterpret_cast<DWORD_PTR>(imageBase) + importDescriptor->Name);

			if (!_stricmp(targetDll, reinterpret_cast<const char*>(libraryName)))
			{
				PIMAGE_THUNK_DATA originalFirstThunk = reinterpret_cast<PIMAGE_THUNK_DATA>(reinterpret_cast<DWORD_PTR>(imageBase) + importDescriptor->OriginalFirstThunk);
				PIMAGE_THUNK_DATA firstThunk = reinterpret_cast<PIMAGE_THUNK_DATA>(reinterpret_cast<DWORD_PTR>(imageBase) + importDescriptor->FirstThunk);

				while (originalFirstThunk->u1.AddressOfData != NULL)
				{
					functionName = reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(reinterpret_cast<DWORD_PTR>(imageBase) + originalFirstThunk->u1.AddressOfData);

					if (!_stricmp(targetFunction, functionName->Name))
					{
						DWORD_PTR originalImport = firstThunk->u1.Function;

						DWORD oldProtection;
						::VirtualProtect(reinterpret_cast<LPVOID>(&firstThunk->u1.Function), sizeof(DWORD_PTR), PAGE_READWRITE, &oldProtection);

						firstThunk->u1.Function = reinterpret_cast<DWORD_PTR>(hookMethod);

						::VirtualProtect(reinterpret_cast<LPVOID>(&firstThunk->u1.Function), sizeof(DWORD_PTR), oldProtection, &oldProtection);

						return reinterpret_cast<void*>(originalImport);
					}
					++originalFirstThunk;
					++firstThunk;
				}
			}
			importDescriptor++;
		}

		return NULL;
	}
}
