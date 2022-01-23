#include "DirectX.h"

#include "Windows.h"
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "mutex"

#include "include/spdlog/spdlog.h"

#include "Render/GUI.h"
#include "Utilities/Hooking.h"

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

static std::once_flag isInitialised;

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

void CreateRenderTarget(IDXGISwapChain* swapChain)
{
    ID3D11Texture2D* renderTarget;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&renderTarget));
    device->CreateRenderTargetView(renderTarget, nullptr, &renderTargetView);
    renderTarget->Release();
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
    namespace DirectX
    {
        void Install()
        {
            HookD3D11();
            HookMouse();
        }

        void Uninstall()
        {
            UnhookD3D11();
            UnhookMouse();
        }
    }
}