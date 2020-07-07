#pragma once

#include <Windows.h>

#include <memory>

class Hooks
{
public:
    Hooks(HMODULE module);
    void Install();
    void Uninstall();

private:
    HMODULE module = NULL;
    HWND window = NULL;
};

inline std::unique_ptr<Hooks> hooks;