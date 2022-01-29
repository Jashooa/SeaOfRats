#include <Windows.h>
#include <TlHelp32.h>

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

DWORD GetProcessIdByName(const std::wstring& processName)
{
    PVOID processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 processEntry{};
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    DWORD processId = 0;
    while (Process32Next(processSnapshot, &processEntry))
    {
        if (wcscmp(processEntry.szExeFile, processName.c_str()) == 0)
        {
            processId = processEntry.th32ProcessID;
            break;
        }
    }

    CloseHandle(processSnapshot);
    return processId;
}

bool HasModule(const DWORD processId, const std::wstring& moduleName)
{
    bool status = false;

    PVOID moduleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
    MODULEENTRY32 moduleEntry = {};
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    while (Module32Next(moduleSnapshot, &moduleEntry))
    {
        if (wcscmp(moduleEntry.szModule, moduleName.c_str()) == 0)
        {
            status = true;
            break;
        }
    }

    CloseHandle(moduleSnapshot);
    return status;
}

bool RemoteInject(const HANDLE& processHandle, const std::wstring& modulePath)
{
    const size_t length = modulePath.capacity() * sizeof(wchar_t);

    LPVOID remoteAddress = VirtualAllocEx(processHandle, NULL, length, MEM_COMMIT, PAGE_READWRITE);
    if (!remoteAddress)
    {
        return false;
    }

    if (!WriteProcessMemory(processHandle, remoteAddress, modulePath.data(), length, NULL))
    {
        return false;
    }

    HANDLE threadHandle = CreateRemoteThread(processHandle, NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryW), remoteAddress, 0, NULL);
    if(!threadHandle)
    {
        return false;
    }

    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    VirtualFreeEx(processHandle, remoteAddress, 0, MEM_RELEASE);
    CloseHandle(processHandle);

    return true;
}

int wmain(int argc, wchar_t* argv[])
{
    const std::wstring processName = L"SoTGame.exe";
    const std::wstring moduleName = L"SeaOfRats.dll";
    const fs::path modulePath = fs::path(fs::current_path().wstring() + L"\\" + moduleName);

    const DWORD processId = GetProcessIdByName(processName);
    if (!processId)
    {
        std::wcout << L"Game process not found." << std::endl;
        system("pause");
        return 1;
    }

    const HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (processHandle == INVALID_HANDLE_VALUE)
    {
        std::wcout << L"Couldn't open process." << std::endl;
        system("pause");
        return 1;
    }

    if (HasModule(processId, moduleName))
    {
        std::wcout << L"Module is already loaded." << std::endl;
        system("pause");
        return 1;
    }

    if (!RemoteInject(processHandle, modulePath.wstring()))
    {
        std::wcout << L"Injection failed." << std::endl;
        system("pause");
        return 1;
    }

    std::wcout << L"Successfully injected." << std::endl;
    return 0;
}
