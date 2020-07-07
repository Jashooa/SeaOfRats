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

LRESULT CALLBACK hWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGuiIO& io = ImGui::GetIO();
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(hWnd, &mousePosition);
    io.MousePos.x = static_cast<float>(mousePosition.x);
    io.MousePos.y = static_cast<float>(mousePosition.y);

    if (uMsg == WM_KEYUP)
    {
        if (wParam == VK_INSERT)
        {
            gui->isOpen = !gui->isOpen;
        }

    }

    if (gui->isOpen)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
        return true;
    }

    return CallWindowProc(originalWndProcHandler, hWnd, uMsg, wParam, lParam);
}

void GUI::Initialise(IDXGISwapChain* swapChain)
{
    DXGI_SWAP_CHAIN_DESC desc;
    swapChain->GetDesc(&desc);

    ID3D11Device* device;
    swapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&device));

    device->GetImmediateContext(&context);

    window = desc.OutputWindow;
    originalWndProcHandler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hWndProc)));

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, context);

    ImGui_ImplDX11_CreateDeviceObjects();
    
    ID3D11Texture2D* renderTargetTexture;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture));
    device->CreateRenderTargetView(renderTargetTexture, nullptr, &mainRenderTargetView);
    renderTargetTexture->Release();
}

void GUI::Destroy()
{
    SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWndProcHandler));

    ImGui_ImplWin32_Shutdown();
    ImGui_ImplDX11_Shutdown();
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
    context->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}