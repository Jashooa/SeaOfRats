#pragma once

#include <mutex>

namespace Hooks
{
    void Install();
    void Uninstall();

    static std::mutex Lock;
}