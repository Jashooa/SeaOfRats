#include "Hooks.h"

#include <Windows.h>
#include <Psapi.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "include/SDK/SDK.h"
#include "include/spdlog/spdlog.h"

#include "GUI.h"
#include "Hacks/Hacks.h"
#include "Utilities/Memory.h"
#include "Utilities/Hooking.h"

using namespace SDK;

static void** swapChainVTable = nullptr;
using Present = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT);
static Present OriginalPresent = nullptr;
const size_t presentIndex = 8;

using ResizeBuffers = HRESULT(__stdcall*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
static ResizeBuffers OriginalResizeBuffers = nullptr;
const size_t resizeBuffersIndex = 13;

using SetCursorProto = HCURSOR(__stdcall*)(HCURSOR);
static SetCursorProto OriginalSetCursor = nullptr;

using SetCursorPosProto = BOOL(__stdcall*)(int, int);
static SetCursorPosProto OriginalSetCursorPos = nullptr;

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

static std::once_flag isInitialised;

void HookGame()
{
    MODULEINFO modInfo{};
    GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &modInfo, sizeof MODULEINFO);
    const auto start = reinterpret_cast<uintptr_t>(modInfo.lpBaseOfDll);
    const auto length = modInfo.SizeOfImage;
    spdlog::info("Module Start: {:p}", reinterpret_cast<void*>(start));
    spdlog::info("Module Length: 0x{:x}", length);

    const auto gObjectsAddress = Utilities::FindPattern(start, length, reinterpret_cast<const unsigned char*>("\x89\x0D\x00\x00\x00\x00\x48\x8B\xDF\x48\x89\x5C\x24"), "xx????xxxxxxx");
    const auto gObjectsOffset = *reinterpret_cast<uint32_t*>(gObjectsAddress + 2);
    UObject::GObjects = reinterpret_cast<decltype(UObject::GObjects)>(gObjectsAddress + gObjectsOffset + 6);
    spdlog::info("gObjectsAddress Address: {:p}", reinterpret_cast<void*>(gObjectsAddress));
    spdlog::info("GObjects Address: {:p}", reinterpret_cast<void*>(UObject::GObjects));
    spdlog::info("GObjects.Num(): {}", UObject::GetObjects().Num());

    const auto gNamesAddress = Utilities::FindPattern(start, length, reinterpret_cast<const unsigned char*>("\x48\x8B\x1D\x00\x00\x00\x00\x48\x85\x00\x75\x3D"), "xxx????xx?xx");
    const auto gNamesOffset = *reinterpret_cast<uint32_t*>(gNamesAddress + 3);
    FName::GNames = reinterpret_cast<decltype(FName::GNames)>(*reinterpret_cast<uintptr_t*>(gNamesAddress + gNamesOffset + 7));
    spdlog::info("gNamesAddress Address: {:p}", reinterpret_cast<void*>(gNamesAddress));
    spdlog::info("GNames Address: {:p}", reinterpret_cast<void*>(FName::GNames));
    spdlog::info("GNames.Num(): {}", FName::GetNames().Num());

    const auto gWorldAddress = Utilities::FindPattern(start, length, reinterpret_cast<const unsigned char*>("\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x88\x00\x00\x00\x00\x48\x85\xC9\x74\x06\x48\x8B\x49\x70"), "xxx????xxx????xxxxxxxxx");
    const auto gWorldOffset = *reinterpret_cast<uint32_t*>(gWorldAddress + 3);
    UWorld::GWorld = reinterpret_cast<decltype(UWorld::GWorld)>(gWorldAddress + gWorldOffset + 7);
    spdlog::info("gWorldAddress Address: {:p}", reinterpret_cast<void*>(gWorldAddress));
    spdlog::info("GWorld Address: {:p}", reinterpret_cast<void*>(UWorld::GWorld));

    UAthenaGameViewportClient::GAthenaGameViewportClient = UObject::FindObject<UAthenaGameViewportClient>("AthenaGameViewportClient Transient.AthenaGameEngine_1.AthenaGameViewportClient_1");
    spdlog::info("AthenaGameViewportClient Address: {:p}", reinterpret_cast<void*>(UAthenaGameViewportClient::GAthenaGameViewportClient));

    const auto uobject = UObject::FindObject<UObject>("Class CoreUObject.Object");
    spdlog::info("Object Address: {:p}", reinterpret_cast<void*>(uobject));

    const auto uclass = UObject::FindObject<UClass>("Class CoreUObject.Class");
    spdlog::info("Class Address: {:p}", reinterpret_cast<void*>(uclass));

    const auto uworld = UObject::FindObject<UWorld>("Class Engine.World");
    spdlog::info("World Address: {:p}", reinterpret_cast<void*>(uworld));
}

void CreateRenderTarget(IDXGISwapChain* swapChain)
{
    ID3D11Texture2D* renderTarget = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTarget));
    if (renderTarget != NULL)
    {
        device->CreateRenderTargetView(renderTarget, nullptr, &renderTargetView);
        renderTarget->Release();
    }
}

HRESULT __stdcall HookedPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    std::call_once(isInitialised, [&]()
        {
            swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));
            device->GetImmediateContext(&immediateContext);

            CreateRenderTarget(swapChain);

            DXGI_SWAP_CHAIN_DESC desc;
            swapChain->GetDesc(&desc);

            gui->Initialise(desc.OutputWindow, device, immediateContext);
        });

    immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    gui->Render();

    return OriginalPresent(swapChain, syncInterval, flags);
}

HRESULT __stdcall HookedResizeBuffers(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
{
    gui->BeforeResize();
    renderTargetView->Release();

    HRESULT result = OriginalResizeBuffers(swapChain, bufferCount, width, height, newFormat, swapChainFlags);

    gui->AfterResize();
    CreateRenderTarget(swapChain);

    return result;
}

void HookD3D11()
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
    sd.OutputWindow = GetForegroundWindow();
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Windowed = 1;

    IDXGISwapChain* swapChain = nullptr;
    ID3D11Device* tempDevice = nullptr;
    ID3D11DeviceContext* tempContext = nullptr;

    HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &sd, &swapChain, &tempDevice, &featureLevel, &tempContext);
    if (FAILED(result))
    {
        spdlog::error("Failed to create device and swapchain");
        return;
    }

    swapChainVTable = *reinterpret_cast<void***>(swapChain);
    OriginalPresent = reinterpret_cast<Present>(Utilities::VMTHook(swapChainVTable, presentIndex, HookedPresent));
    OriginalResizeBuffers = reinterpret_cast<ResizeBuffers>(Utilities::VMTHook(swapChainVTable, resizeBuffersIndex, HookedResizeBuffers));

    tempContext->Release();
    tempDevice->Release();
    swapChain->Release();
}

void UnhookD3D11()
{
    renderTargetView->Release();
    Utilities::VMTHook(swapChainVTable, presentIndex, OriginalPresent);
    Utilities::VMTHook(swapChainVTable, resizeBuffersIndex, OriginalResizeBuffers);
}

HCURSOR __stdcall HookedSetCursor(HCURSOR hCursor)
{
    if (gui->isOpen)
    {
        return 0;
    }

    return OriginalSetCursor(hCursor);
}

BOOL __stdcall HookedSetCursorPos(int X, int Y)
{
    if (gui->isOpen)
    {
        return FALSE;
    }

    return OriginalSetCursorPos(X, Y);
}

void HookMouse()
{
    OriginalSetCursor = reinterpret_cast<SetCursorProto>(Utilities::IATHook("USER32.dll", "SetCursor", HookedSetCursor));
    OriginalSetCursorPos = reinterpret_cast<SetCursorPosProto>(Utilities::IATHook("USER32.dll", "SetCursorPos", HookedSetCursorPos));
}

void UnhookMouse()
{
    Utilities::IATHook("USER32.dll", "SetCursor", OriginalSetCursor);
    Utilities::IATHook("USER32.dll", "SetCursorPos", OriginalSetCursorPos);
}

namespace Hooks
{
    void Install()
    {
        HookGame();
        HookMouse();
        HookD3D11();
    }

    void Uninstall()
    {
        Lock.lock();
        UnhookD3D11();
        Lock.unlock();
        UnhookMouse();
    }
}
