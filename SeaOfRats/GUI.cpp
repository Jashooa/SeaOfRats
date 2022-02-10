#include "GUI.h"

#include <Windows.h>
#include <d3d11.h>

#include <string>

#include "include/imgui/imgui.h"
#include "include/imgui/imgui_impl_dx11.h"
#include "include/imgui/imgui_impl_win32.h"
#include "include/imgui/imgui_internal.h"

#include "Config.h"
#include "Drawing.h"
#include "Hooks.h"
#include "SeaOfRats.h"
#include "Hacks/Hacks.h"

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
    /*ImGuiIO& io = ImGui::GetIO();
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
        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        LPWSTR win32_cursor = IDC_ARROW;
        switch (imgui_cursor)
        {
            case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
            case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
            case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
            case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
            case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
            case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
            case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
            case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
            case ImGuiMouseCursor_NotAllowed:   win32_cursor = IDC_NO; break;
        }
        SetCursor(LoadCursorW(nullptr, win32_cursor));

        return ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam);
    }

    return CallWindowProc(originalWndProcHandler, handle, message, wParam, lParam);*/

    if (message == WM_KEYUP && wParam == VK_INSERT)
    {
        gui->isOpen = !gui->isOpen;
    }

    if (gui->isOpen && ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam))
    {
        return true;
    }

    if (gui->isOpen)
    {
        ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();
        LPWSTR win32_cursor = IDC_ARROW;
        switch (imgui_cursor)
        {
            case ImGuiMouseCursor_Arrow:        win32_cursor = IDC_ARROW; break;
            case ImGuiMouseCursor_TextInput:    win32_cursor = IDC_IBEAM; break;
            case ImGuiMouseCursor_ResizeAll:    win32_cursor = IDC_SIZEALL; break;
            case ImGuiMouseCursor_ResizeEW:     win32_cursor = IDC_SIZEWE; break;
            case ImGuiMouseCursor_ResizeNS:     win32_cursor = IDC_SIZENS; break;
            case ImGuiMouseCursor_ResizeNESW:   win32_cursor = IDC_SIZENESW; break;
            case ImGuiMouseCursor_ResizeNWSE:   win32_cursor = IDC_SIZENWSE; break;
            case ImGuiMouseCursor_Hand:         win32_cursor = IDC_HAND; break;
            case ImGuiMouseCursor_NotAllowed:   win32_cursor = IDC_NO; break;
        }
        SetCursor(LoadCursor(nullptr, win32_cursor));

        return DefWindowProc(handle, message, wParam, lParam);
    }  

    return CallWindowProc(originalWndProcHandler, handle, message, wParam, lParam);
}

namespace GUI
{
    GUI::GUI()
    {
        ImGui::CreateContext();

        ImGuiStyle& style = ImGui::GetStyle();

        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        io.LogFilename = nullptr;

        io.Fonts->AddFontDefault();
        io.Fonts->Build();
        ImGui::GetDefaultFont()->AddRemapChar(0x2019, 0x0027);
    }

    void GUI::Initialise(HWND outputWindow, ID3D11Device* device, ID3D11DeviceContext* context)
    {
        window = outputWindow;
        originalWndProcHandler = reinterpret_cast<WNDPROC>(SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hookWndProc)));

        ImGui_ImplWin32_Init(window);
        ImGui_ImplDX11_Init(device, context);
        ImGui_ImplDX11_CreateDeviceObjects();
    }

    void GUI::BeforeResize()
    {
        ImGui_ImplDX11_InvalidateDeviceObjects();
    }

    void GUI::AfterResize()
    {
        ImGui_ImplDX11_CreateDeviceObjects();
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

        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

        ImGuiIO& io = ImGui::GetIO();

        ImGui::Begin("#1", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

        Drawing::Window = ImGui::GetCurrentWindow();

        Hooks::Lock.lock();
        Hacks::Loop();
        Hooks::Lock.unlock();

        ImGui::End();

        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);

        if (isOpen)
        {
            ImGui::Begin("SeaOfRats", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

            if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_NoTooltip))
            {
                if (ImGui::BeginTabItem("ESP"))
                {
                    ImGui::Text("Entities");
                    ImGui::Checkbox("Player##ESP", &config.esp.player.enable);
                    ImGui::Checkbox("Skeleton##ESP", &config.esp.skeleton.enable);
                    ImGui::Checkbox("Animal##ESP", &config.esp.animal.enable);
                    ImGui::Checkbox("Mermaid##ESP", &config.esp.mermaid.enable);
                    ImGui::Checkbox("Siren##ESP", &config.esp.siren.enable);
                    ImGui::Checkbox("Shark##ESP", &config.esp.shark.enable);
                    ImGui::Checkbox("Megalodon##ESP", &config.esp.megalodon.enable);
                    ImGui::Checkbox("Kraken##ESP", &config.esp.kraken.enable);

                    ImGui::Separator();

                    ImGui::Text("Vehicles");
                    ImGui::Checkbox("Ship##ESP", &config.esp.ship.enable);
                    ImGui::Checkbox("Ghost Ship##ESP", &config.esp.ghostship.enable);
                    ImGui::Checkbox("Rowboat##ESP", &config.esp.rowboat.enable);

                    ImGui::Separator();

                    ImGui::Text("Items");
                    ImGui::Checkbox("Item##ESP", &config.esp.item.enable);
                    ImGui::Checkbox("Barrel##ESP", &config.esp.barrel.enable);
                    ImGui::Checkbox("Lore Book##ESP", &config.esp.lorebook.enable);

                    ImGui::Separator();

                    ImGui::Text("Misc");
                    ImGui::Checkbox("Map Pin##ESP", &config.esp.mappin.enable);
                    ImGui::Checkbox("Storm##ESP", &config.esp.storm.enable);
                    ImGui::Checkbox("Treasure Map##ESP", &config.esp.treasuremap.enable);
                    ImGui::Checkbox("Enchanted Compass##ESP", &config.esp.enchantedcompass.enable);
                    ImGui::Checkbox("Skeleton Throne##ESP", &config.esp.skeletonthrone.enable);

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Info"))
                {
                    ImGui::Checkbox("Crosshair##Info", &config.info.crosshair);
                    ImGui::Checkbox("Playerlist##Info", &config.info.playerList);
                    ImGui::Checkbox("Compass##Info", &config.info.compass);
                    ImGui::Checkbox("Oxygen##Info", &config.info.oxygen);
                    ImGui::Checkbox("Water Level##Info", &config.info.waterLevel);
                    ImGui::Checkbox("Anchor##Info", &config.info.anchor);
                    ImGui::Checkbox("Debug##Info", &config.info.debug);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Client"))
                {
                    ImGui::Checkbox("Anti AFK##Client", &config.client.antiafk);
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Aimbot"))
                {
                    ImGui::Text("Global");
                    ImGui::Checkbox("Enabled##Aim", &config.aim.enable);

                    ImGui::Separator();

                    ImGui::Text("Player");
                    ImGui::Checkbox("Enable##PlayerAim", &config.aim.player.enable);
                    ImGui::Checkbox("Players##PlayerAim", &config.aim.player.player);
                    ImGui::Checkbox("Skeletons##PlayerAim", &config.aim.player.skeleton);

                    ImGui::Separator();

                    ImGui::Text("Cannon");
                    ImGui::Checkbox("Enable##CannonAim", &config.aim.cannon.enable);
                    ImGui::Checkbox("Path##CannonAim", &config.aim.cannon.path);

                    ImGui::EndTabItem();
                }

                if (ImGui::TabItemButton("Unload", ImGuiTabItemFlags_Trailing))
                {
                    seaofrats->Uninstall();
                }

                ImGui::EndTabBar();
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }
}
