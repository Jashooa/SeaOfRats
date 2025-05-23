#include "UE4.h"

namespace SDK
{
    TNameEntryArray* FName::GNames = nullptr;
    FUObjectArray* UObject::GObjects = nullptr;

    bool FWeakObjectPtr::IsValid() const
    {
        if (ObjectSerialNumber == 0)
        {
            return false;
        }
        if (ObjectIndex < 0)
        {
            return false;
        }
        auto ObjectItem = UObject::GetObjects().GetItemByIndex(ObjectIndex);
        if (!ObjectItem)
        {
            return false;
        }
        if (!SerialNumbersMatch(ObjectItem))
        {
            return false;
        }
        return !(ObjectItem->IsUnreachable() || ObjectItem->IsPendingKill());
    }

    UObject* FWeakObjectPtr::Get() const
    {
        if (IsValid())
        {
            auto ObjectItem = UObject::GetObjects().GetItemByIndex(ObjectIndex);
            if (ObjectItem)
            {
                return ObjectItem->Object;
            }
        }
        return nullptr;
    }
}
