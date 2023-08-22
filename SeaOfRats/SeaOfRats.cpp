#include "SeaOfRats.h"

#include <filesystem>
#include <string>

#include "include/spdlog/spdlog.h"
#include "include/spdlog/sinks/basic_file_sink.h"

#include "Config.h"
#include "Hooks.h"
#include "GUI.h"

SeaOfRats::SeaOfRats(HMODULE module)
{
    this->module = module;

    char buffer[MAX_PATH];
    GetModuleFileNameA(module, buffer, MAX_PATH);
    const auto logPath = std::filesystem::path(buffer).remove_filename() / "log.txt";

    /*auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logPath.string(), true);
    auto console_sink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
    spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({ file_sink, console_sink })));*/

    spdlog::set_default_logger(spdlog::basic_logger_st("file", logPath.string(), true));
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%L%$] %v");
    spdlog::set_level(spdlog::level::info);
    spdlog::flush_on(spdlog::level::info);

    spdlog::info("Initialising SeaOfRats");
}

static DWORD WINAPI Load()
{
    spdlog::info("Loading");

    //config = std::make_unique<Config>();
    gui = std::make_unique<GUI::GUI>();

    spdlog::info("Installing Hooks");
    Hooks::Install();

    spdlog::info("Done Hooking");
    ExitThread(0);
}

void SeaOfRats::Install()
{
    if (auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Load), nullptr, 0, nullptr))
    {
        CloseHandle(thread);
    }
}

static DWORD WINAPI Unload(HMODULE module)
{
    spdlog::info("Unloading");

    spdlog::info("Uninstalling Hooks");
    Hooks::Uninstall();

    gui->Destroy();

    spdlog::info("Done Unloading");
    spdlog::shutdown();

    FreeLibraryAndExitThread(module, 0);
}

void SeaOfRats::Uninstall()
{
    if (auto thread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Unload), module, 0, nullptr))
    {
        CloseHandle(thread);
    }
}
