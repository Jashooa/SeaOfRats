#include "Game.h"

#include <Windows.h>
#include <Psapi.h>

#include "mutex"

#include "SDK/SDK.h"
#include "spdlog/spdlog.h"

#include "Hacks/Drawing.h"
#include "Hacks/ESP.h"
#include "Hacks/Info.h"
#include "Utilities/Memory.h"
#include "Utilities/VMTHook.h"

using namespace SDK;

static void** clientVTable = nullptr;
using PostRender = void(__thiscall*)(UGameViewportClient*, UCanvas*);
static PostRender originalPostRender = nullptr;
const size_t postRenderIndex = 88;

std::mutex hookLock;

bool NullChecks(UGameViewportClient* client)
{
    if (!client->World)
    {
        spdlog::warn("World null");
        return false;
    }
    if (!client->World->GameState)
    {
        spdlog::warn("GameState null");
        return false;
    }
    if (!client->World->GameState->IsA(AAthenaGameState::StaticClass()))
    {
        return false;
    }
    if (!client->World->PersistentLevel)
    {
        spdlog::warn("PersistentLevel null");
        return false;
    }
    if (!client->GameInstance)
    {
        spdlog::warn("GameInstance null");
        return false;
    }
    if (client->GameInstance->LocalPlayers.Num() < 1)
    {
        spdlog::warn("LocalPlayers < 1");
        return false;
    }
    if (!client->GameInstance->LocalPlayers[0]->PlayerController)
    {
        spdlog::warn("PlayerController null");
        return false;
    }
    if (!client->GameInstance->LocalPlayers[0]->PlayerController->Pawn)
    {
        spdlog::warn("Pawn null");
        return false;
    }
    return true;
}

void hookedPostRender(UGameViewportClient* client, UCanvas* canvas)
{
    hookLock.lock();
    if (NullChecks(client))
    {
        AHUD* hud = client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD;
        hud->Canvas = canvas;
        Hacks::RenderESP(client, hud);
        Hacks::RenderInfo(client, hud);
    }
    hookLock.unlock();

    return originalPostRender(client, canvas);
}

void hookGame()
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
    originalPostRender = reinterpret_cast<PostRender>(Utilities::HookMethod(clientVTable, postRenderIndex, hookedPostRender));
}

namespace Hooks
{
    namespace Game
    {
        void Install()
        {
            hookGame();
        }

        void Uninstall()
        {
            hookLock.lock();
            Utilities::HookMethod(clientVTable, postRenderIndex, originalPostRender);
            hookLock.unlock();
        }
    }
}