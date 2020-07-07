#pragma once

#include <d3d11.h>
#include <Windows.h>

#include <memory>

class GUI
{
public:
    GUI();
    void Initialise(IDXGISwapChain* swapChain);
    void Destroy();
    void Render();

    bool isOpen = true;

private:
    ID3D11RenderTargetView* mainRenderTargetView = nullptr;
    ID3D11DeviceContext* context = nullptr;

    HWND window = NULL;
};

inline std::unique_ptr<GUI> gui;