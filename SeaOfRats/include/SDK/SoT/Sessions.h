#pragma once

namespace SDK
{
    // ScriptStruct Sessions.SessionTemplate
    // 0x0018
    struct FSessionTemplate
    {
        char pad_0x0000[0x0014];
        int MaxPlayers; // 0x0014(0x0004)
    };

    // ScriptStruct Sessions.CrewSessionTemplate
    // 0x0020 (0x0038 - 0x0018)
    struct FCrewSessionTemplate : public FSessionTemplate
    {
        char pad_0x0018[0x0018];
        int MaxMatchmakingPlayers; // 0x0030(0x0004)
        char pad_0x0034[0x0004];
    };
}
