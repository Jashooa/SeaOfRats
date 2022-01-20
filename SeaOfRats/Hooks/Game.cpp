#include "Game.h"

#include <Windows.h>
#include <Psapi.h>

#include "mutex"

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "Hacks/Drawing.h"
#include "Hacks/Hacks.h"
#include "Utilities/Memory.h"
#include "Utilities/VMTHook.h"

using namespace SDK;

static void** clientVTable = nullptr;
using PostRender = void(__thiscall*)(UGameViewportClient*, UCanvas*);
static PostRender OriginalPostRender = nullptr;
const size_t postRenderIndex = 91;

std::mutex hookLock;

void HookedPostRender(UGameViewportClient* client, UCanvas* canvas)
{
    hookLock.lock();
    Hacks::Loop(client, canvas);
    hookLock.unlock();

    return OriginalPostRender(client, canvas);
}

void HookGame()
{
    MODULEINFO modInfo{ 0 };
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof MODULEINFO);
    const auto start = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
    const auto length = modInfo.SizeOfImage;
    spdlog::info("Module Start: {:p}", reinterpret_cast<void*>(start));
    spdlog::info("Module Length: 0x{:x}", length);

    const auto gObjectsAddress = Utilities::FindPattern(start, length, reinterpret_cast<const unsigned char*>("\x89\x0D\x00\x00\x00\x00\x48\x8B\xDF\x48\x89\x5C\x24"), "xx????xxxxxxx");
    const auto gObjectsOffset = *reinterpret_cast<uint32_t*>(gObjectsAddress + 2);
    UObject::GObjects = reinterpret_cast<decltype(UObject::GObjects)>(gObjectsAddress + gObjectsOffset + 6);
    spdlog::info("GObjects Address: {:p}", reinterpret_cast<void*>(UObject::GObjects));
    spdlog::info("GObjects.Num(): {}", UObject::GetGlobalObjects().Num());

    const auto gNamesAddress = Utilities::FindPattern(start, length, reinterpret_cast<const unsigned char*>("\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\x00\x75\x3D"), "xxx????xx?xx");
    const auto gNamesOffset = *reinterpret_cast<uint32_t*>(gNamesAddress + 3);
    FName::GNames = reinterpret_cast<decltype(FName::GNames)>(*reinterpret_cast<uintptr_t*>(gNamesAddress + gNamesOffset + 7));
    spdlog::info("GNames Address: {:p}", reinterpret_cast<void*>(FName::GNames));
    spdlog::info("GNames.Num(): {}", FName::GetGlobalNames().Num());

    const auto gameViewportClient = UObject::FindObject<UAthenaGameViewportClient>("AthenaGameViewportClient Transient.AthenaGameEngine_1.AthenaGameViewportClient_1");
    spdlog::info("AthenaGameViewportClient Address: {:p}", reinterpret_cast<void*>(gameViewportClient));

    Hacks::Drawing::RobotoFont = UObject::FindObject<UFont>("Font Roboto.Roboto");
    Hacks::Drawing::RobotoTinyFont = UObject::FindObject<UFont>("Font RobotoTiny.RobotoTiny");

    const auto uobject = UObject::FindObject<UAthenaGameViewportClient>("Class CoreUObject.Object");
    spdlog::info("Object Address: {:p}", reinterpret_cast<void*>(uobject));

    const auto uclass = UObject::FindObject<UAthenaGameViewportClient>("Class CoreUObject.Class");
    spdlog::info("Class Address: {:p}", reinterpret_cast<void*>(uclass));

    clientVTable = *reinterpret_cast<void***>(gameViewportClient);
    OriginalPostRender = reinterpret_cast<PostRender>(Utilities::HookMethod(clientVTable, postRenderIndex, HookedPostRender));
}

namespace Hooks
{
    namespace Game
    {
        void Install()
        {
            HookGame();
        }

        void Uninstall()
        {
            hookLock.lock();
            Utilities::HookMethod(clientVTable, postRenderIndex, OriginalPostRender);
            hookLock.unlock();
        }
    }
}