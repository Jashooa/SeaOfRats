#pragma once

#include <Windows.h>
#include <d3d11.h>

#include <memory>

namespace GUI
{
    class GUI
    {
    public:
        GUI();
        void Initialise(HWND window, ID3D11Device* device, ID3D11DeviceContext* context);
        void BeforeResize();
        void AfterResize();
        void Destroy();
        void Render();
        bool isOpen = true;
    private:
        HWND window = nullptr;
    };
}

inline std::unique_ptr<GUI::GUI> gui;
