#include "GUI.h"

#include <d3d11.h>
#include <Windows.h>

#include <string>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_dx11.h"
#include "include/imgui/imgui_impl_win32.h"

#include "Hooks.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC originalWndProcHandler = nullptr;

GUI::GUI()
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
}

bool shouldImGuiHandle(const UINT message)
{
    switch (message)
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_MOUSEMOVE:
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        case WM_CHAR:
            return true;
        default:
            return false;
    }
}

LRESULT CALLBACK hookWndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(handle, &mousePosition);
    io.MousePos.x = static_cast<float>(mousePosition.x);
    io.MousePos.y = static_cast<float>(mousePosition.y);

    if (message == WM_KEYUP && wParam == VK_INSERT)
    {
        gui->isOpen = !gui->isOpen;
    }

    if (gui->isOpen && shouldImGuiHandle(message))
    {
        return ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam);
    }

    return CallWindowProc(originalWndProcHandler, handle, message, wParam, lParam);
}

void GUI::Initialise(IDXGISwapChain* swapChain)
{
    DXGI_SWAP_CHAIN_DESC desc{ 0 };
    swapChain->GetDesc(&desc);

    ID3D11Device* device;
    swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));
    device->GetImmediateContext(&context);

    window = desc.OutputWindow;
    originalWndProcHandler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hookWndProc)));

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, context);

    CreateRenderTarget(swapChain, device);
}

void GUI::BeforeResize()
{
    ImGui_ImplDX11_InvalidateDeviceObjects();
    renderTargetView->Release();
}

void GUI::AfterResize(IDXGISwapChain* swapChain)
{
    ID3D11Device* device;
    swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));
    CreateRenderTarget(swapChain, device);
}

void GUI::CreateRenderTarget(IDXGISwapChain* swapChain, ID3D11Device* device)
{
    ImGui_ImplDX11_CreateDeviceObjects();

    ID3D11Texture2D* buffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer));
    device->CreateRenderTargetView(buffer, nullptr, &renderTargetView);
    buffer->Release();
}

void GUI::Destroy()
{
    SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProcHandler));

    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX11_Shutdown();
    renderTargetView->Release();
    ImGui::DestroyContext();
}

void GUI::Render()
{
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX11_NewFrame();
    ImGui::NewFrame();

    if (isOpen)
    {
        ImGui::Begin("Test");

        ImGui::Text("Hello");

        if (ImGui::Button("Unhook"))
        {
            hooks->Uninstall();
        }

        ImGui::End();
    }

    ImGui::Render();
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}