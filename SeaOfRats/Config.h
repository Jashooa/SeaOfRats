#pragma once

#include <memory>

class Config
{
public:
    Config();
    bool playerESP;
    bool skeletonESP;
    bool sharkESP;
    bool krakenESP;
    bool krakenTentacleESP;
    bool animalESP;
    bool mermaidESP;
    bool shipESP;
    bool farShipESP;
    bool skeletonShipESP;
    bool ghostShipESP;
    bool rowboatESP;
    bool itemESP;
    bool barrelESP;
    bool shipwreckESP;
    bool stormESP;
    bool eventESP;
    bool mapESP;
    bool debugESP;

    bool crosshairInfo;
    bool playerListInfo;
    bool compassInfo;
    bool oxygenInfo;
    bool waterLevelInfo;
    bool anchorInfo;

    bool enabledAimbot;
};

inline std::unique_ptr<Config> config;
