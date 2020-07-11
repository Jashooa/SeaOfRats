#pragma once

#include <memory>

class Config
{
public:
    Config();
    bool playerESP;
    bool skeletonESP;
    bool sharkESP;
    bool mermaidESP;
    bool shipESP;
    bool shipFarESP;
    bool rowboatESP;
    bool itemESP;
    bool mapESP;
    bool debugESP;

    bool crosshair;
    bool compass;
    bool playerList;
};

inline std::unique_ptr<Config> config;