#pragma once

#include <Windows.h>

#include <memory>

class SeaOfRats
{
public:
    SeaOfRats(HMODULE module);
    void Install();
    void Uninstall();

private:
    HMODULE module = NULL;
};

inline std::unique_ptr<SeaOfRats> seaofrats;
