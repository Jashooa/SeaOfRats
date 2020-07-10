#pragma once

#include <memory>

class Config
{
public:
    Config();
    bool playerESP;
    bool skeletonESP;
    bool shipESP;
    bool farShipESP;
    bool itemESP;
    bool mapESP;
    bool debugESP;

    bool crosshair;
    bool compass;
    bool playerList;
};

inline std::shared_ptr<Config> config;