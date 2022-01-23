#include "SeaOfRats.h"

#include <Windows.h>

#include <string>

#include "include/spdlog/spdlog.h"
#include "include/spdlog/async.h"
#include "include/spdlog/sinks/basic_file_sink.h"

#include "Config.h"
#include "Hooks/DirectX.h"
#include "Hooks/Game.h"
#include "Render/GUI.h"

SeaOfRats::SeaOfRats(HMODULE module)
{
    this->module = module;

    /*char* buffer;
    size_t len;
    _dupenv_s(&buffer, &len, "localappdata");
    auto directory = static_cast<std::string>(buffer) + "\\SeaOfRats\\";
    free(buffer);*/

    DWORD len = 65535;
    std::string dataDirectory;
    dataDirectory.resize(len);
    len = GetEnvironmentVariableA("localappdata", &dataDirectory[0], len);
    dataDirectory.resize(len);
    auto directory = dataDirectory + "\\SeaOfRats\\";

    spdlog::set_default_logger(spdlog::basic_logger_mt("SeaOfRats", directory + "log.txt"));
    spdlog::flush_on(spdlog::level::debug);

#if _DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::info("Initialising SeaOfRats");
}

static DWORD WINAPI Load()
{
    spdlog::info("Loading Hooks");

    //config = std::make_unique<Config>();
    gui = std::make_unique<Render::GUI::GUI>();

    spdlog::info("Hooking DirectX");
    Hooks::DirectX::Install();

    spdlog::info("Hooking Game");
    Hooks::Game::Install();

    spdlog::info("Done Hooking");
    ExitThread(0);
}

void SeaOfRats::Install()
{
    if (HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Load), nullptr, 0, nullptr))
    {
        CloseHandle(thread);
    }
}

static DWORD WINAPI Unload(HMODULE module)
{
    spdlog::info("Unloading Hooks");

    Sleep(50);

    spdlog::info("Unhooking Game");
    Hooks::Game::Uninstall();

    spdlog::info("Unhooking DirectX");
    Hooks::DirectX::Uninstall();

    gui->Destroy();

    spdlog::info("Done Unloading");
    spdlog::shutdown();
    FreeLibraryAndExitThread(module, 0);
}

void SeaOfRats::Uninstall()
{
    if (HANDLE thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Unload), module, 0, nullptr))
    {
        CloseHandle(thread);
    }
}
