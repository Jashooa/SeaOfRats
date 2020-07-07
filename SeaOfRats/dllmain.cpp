#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <memory>

#include "Hooks.h"


BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(reserved);

    switch (reason)
    {
        case DLL_PROCESS_ATTACH:
            hooks = std::make_unique<Hooks>(module);
            hooks->Install();
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}
