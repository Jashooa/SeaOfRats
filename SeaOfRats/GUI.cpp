#include "GUI.h"

#include <d3d11.h>
#include <Windows.h>

#include <string>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_dx11.h"
#include "include/imgui/imgui_impl_win32.h"

#include "Config.h"
#include "Hooks.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static WNDPROC originalWndProcHandler = nullptr;

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

GUI::GUI()
{
    ImGui::CreateContext();

    ImGuiStyle& style = ImGui::GetStyle();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
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
    static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;

    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX11_NewFrame();
    ImGui::NewFrame();

    if (isOpen)
    {
        ImGui::Begin("SeaOfRats", nullptr, windowFlags);

        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_NoTooltip))
        {
            if (ImGui::BeginTabItem("ESP"))
            {
                ImGui::Text("Entities");
                ImGui::Checkbox("Player", &config->playerESP);
                ImGui::Checkbox("Skeleton", &config->skeletonESP);
                ImGui::Checkbox("Shark", &config->sharkESP);
                ImGui::Checkbox("Kraken", &config->krakenESP);
                ImGui::Checkbox("Kraken Tentacle", &config->krakenTentacleESP);
                ImGui::Checkbox("Animal", &config->animalESP);
                ImGui::Checkbox("Mermaid", &config->mermaidESP);

                ImGui::Separator();

                ImGui::Text("Ships");
                ImGui::Checkbox("Ship", &config->shipESP);
                ImGui::Checkbox("Far Ship", &config->farShipESP);
                ImGui::Checkbox("Skeleton Ship", &config->skeletonShipESP);
                ImGui::Checkbox("Ghost Ship", &config->ghostShipESP);
                ImGui::Checkbox("Rowboat", &config->rowboatESP);

                ImGui::Separator();

                ImGui::Text("Misc");
                ImGui::Checkbox("Item", &config->itemESP);
                ImGui::Checkbox("Shipwreck", &config->shipwreckESP);
                ImGui::Checkbox("Storm", &config->stormESP);
                ImGui::Checkbox("Event", &config->eventESP);
                ImGui::Checkbox("Map", &config->mapESP);
                ImGui::Checkbox("Debug", &config->debugESP);
            }

            if (ImGui::BeginTabItem("Info"))
            {
                ImGui::Checkbox("Crosshair", &config->crosshair);
                ImGui::Checkbox("Compass", &config->compass);
                ImGui::Checkbox("Playerlist", &config->playerList);
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Aimbot"))
            {

                ImGui::EndTabItem();
            }
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Unload"))
        {
            hooks->Uninstall();
        }
        ImGui::EndTabBar();

        ImGui::End();
    }

    ImGui::Render();
    context->OMSetRenderTargets(1, &renderTargetView, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
