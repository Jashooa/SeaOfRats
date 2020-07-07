#include "Hooks.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <Psapi.h>
#include <Windows.h>

#include <memory>
#include <mutex>
#include <string>

#include "include/spdlog/spdlog.h"
#include "include/spdlog/async.h"
#include "include/spdlog/sinks/basic_file_sink.h"

#include "Config.h"
#include "Drawing.h"
#include "Global.h"
#include "GUI.h"
#include "SDK.hpp"
#include "Hacks/ESP.h"
#include "Hacks/Info.h"
#include "Utilities/Memory.h"
#include "Utilities/VMTHook.h"

using namespace SDK;

static void** swapChainVTable = nullptr;
using Present = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
static Present originalPresent = nullptr;
const size_t presentIndex = 8;

static void** clientVTable = nullptr;
using PostRender = void(__thiscall*)(UGameViewportClient*, UCanvas*);
static PostRender originalPostRender = nullptr;
const size_t postRenderIndex = 88;

static void** objectVTable = nullptr;
using ProcessEvent = void(__thiscall*)(UObject*, UFunction*, void*);
static ProcessEvent originalProcessEvent = nullptr;
const size_t processEventIndex = 58;

static std::once_flag isInitialised;

HRESULT __stdcall hookedPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    std::call_once(isInitialised, [&](){
        gui->Initialise(swapChain);
    });

    gui->Render();

    return originalPresent(swapChain, syncInterval, flags);
}

HRESULT hookD3D11(HWND window)
{
    D3D_FEATURE_LEVEL featureLevel;
    DXGI_SWAP_CHAIN_DESC sd{ 0 };
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.Height = 100;
    sd.BufferDesc.Width = 100;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = window;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Windowed = 1;

    IDXGISwapChain* swapChain = nullptr;
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;

    HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swapChain, &device, &featureLevel, &context);
    if (FAILED(result))
    {
        spdlog::error("Failed to create device and swapchain");
        return E_FAIL;
    }

    swapChainVTable = *reinterpret_cast<void***>(swapChain);
    originalPresent = reinterpret_cast<Present>(Utilities::HookMethod(swapChainVTable, presentIndex, hookedPresent));

    swapChain->Release();
    swapChain = nullptr;

    device->Release();
    device = nullptr;

    context->Release();
    context = nullptr;

    return S_OK;
}

bool NullChecks(UGameViewportClient* client)
{
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
    if (!client->World)
    {
        spdlog::warn("World null");
        return false;
    }
    if (!client->World->PersistentLevel)
    {
        spdlog::warn("PersistentLevel null");
        return false;
    }
    return true;
}

void hookedPostRender(UGameViewportClient* client, UCanvas* canvas)
{
    //if (client->GameInstance->LocalPlayers[0]->PlayerController->Pawn)
    if (NullChecks(client))
    {
        AHUD* hud = client->GameInstance->LocalPlayers[0]->PlayerController->MyHUD;
        hud->Canvas = canvas;
        Hacks::RenderCrosshair(hud);
        Hacks::RenderESP(client, hud);
    }

    originalPostRender(client, canvas);
}

/*void hookedProcessEvent(UObject* object, UFunction* function, void* parms)
{
    spdlog::info("test");
    if (object->IsA(AHUD::StaticClass()))
    {
        auto hud = reinterpret_cast<AHUD*>(object);
        
    }

    originalProcessEvent(object, function, parms);
}*/

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

    Global::GameViewportClient = UObject::FindObject<UAthenaGameViewportClient>("AthenaGameViewportClient Transient.AthenaGameEngine_1.AthenaGameViewportClient_1");
    spdlog::info("AthenaGameViewportClient Address: {:p}", reinterpret_cast<void*>(Global::GameViewportClient));

    Drawing::RobotoFont = UObject::FindObject<UFont>("Font Roboto.Roboto");
    Drawing::RobotoTinyFont = UObject::FindObject<UFont>("Font RobotoTiny.RobotoTiny");

    /*UObject* obj = UObject::FindObject<UObject>("Class CoreUObject.Object");
    spdlog::info("UObject Address: {:p}", reinterpret_cast<void*>(obj));

    objectVTable = *reinterpret_cast<void***>(obj);
    originalProcessEvent = reinterpret_cast<ProcessEvent>(Utilities::HookMethod(objectVTable, processEventIndex, hookedProcessEvent));*/

    clientVTable = *reinterpret_cast<void***>(Global::GameViewportClient);
    originalPostRender = reinterpret_cast<PostRender>(Utilities::HookMethod(clientVTable, postRenderIndex, hookedPostRender));
}

Hooks::Hooks(HMODULE module)
{
    this->module = module;
    this->window = GetForegroundWindow();

    /*char* buffer;
    size_t len;
    _dupenv_s(&buffer, &len, "localappdata");
    auto directory = static_cast<std::string>(buffer) + "\\SeaOfRats\\";
    free(buffer);*/

    DWORD len = 65535;
    std::string dataDirectory;
    dataDirectory.resize(len);
    len = GetEnvironmentVariableA("localappdata", &dataDirectory[0], len);
    dataDirectory.resize(len);
    auto directory = dataDirectory + "\\SeaOfRats\\";

    spdlog::set_default_logger(spdlog::basic_logger_mt("SeaOfRats", directory + "log.txt"));
    spdlog::flush_on(spdlog::level::debug);

#if _DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::info("Initialising SeaOfRats");
}

static DWORD WINAPI Load(HWND window)
{
    spdlog::info("Loading Hooks");

    config = std::make_unique<Config>();
    gui = std::make_unique<GUI>();

    spdlog::info("Hooking DirectX");
    hookD3D11(window);

    spdlog::info("Hooking Game");
    hookGame();

    spdlog::info("Done Hooking");
    ExitThread(0);
}

void Hooks::Install()
{
    if (HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Load), window, 0, nullptr))
    {
        CloseHandle(thread);
    }
}

static DWORD WINAPI Unload(HMODULE module)
{
    spdlog::info("Unloading Hooks");

    Sleep(50);

    spdlog::info("Unhooking Game");
    Utilities::HookMethod(clientVTable, postRenderIndex, originalPostRender);
    //Utilities::HookMethod(objectVTable, processEventIndex, originalProcessEvent);

    spdlog::info("Unhooking DirectX");
    Utilities::HookMethod(swapChainVTable, presentIndex, originalPresent);

    gui->Destroy();

    spdlog::info("Done Unloading");
    FreeLibraryAndExitThread(module, 0);
}

void Hooks::Uninstall()
{
    if (HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Unload), module, 0, nullptr))
    {
        CloseHandle(thread);
    }
}