#ifdef _MSC_VER
    #pragma pack(push, 0x8)
#endif

#include "UE4.h"

namespace SDK
{
    TNameEntryArray* FName::GNames = nullptr;
    FUObjectArray* UObject::GObjects = nullptr;
}

#ifdef _MSC_VER
    #pragma pack(pop)
#endif
