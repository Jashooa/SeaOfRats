#pragma once

#include <string>

#include "Basic.h"

namespace SDK
{
    // ScriptStruct CoreUObject.StringAssetReference
    // 0x0010
    struct FStringAssetReference
    {
        class FString AssetLongPathname; // 0x0000(0x0010)
    };

    // ScriptStruct CoreUObject.FloatRangeBound
    // 0x0008
    struct FFloatRangeBound
    {
        char pad_0x0000[0x0004];
        float Value; // 0x0004(0x0004)
    };

    // ScriptStruct CoreUObject.FloatRange
    // 0x0010
    struct FFloatRange
    {
        struct FFloatRangeBound LowerBound; // 0x0000(0x0008)
        struct FFloatRangeBound UpperBound; // 0x0008(0x0008)
    };

    // ScriptStruct CoreUObject.Int32RangeBound
    // 0x0008
    struct FInt32RangeBound
    {
        char pad_0x0000[0x0004];
        int Value; // 0x0004(0x0004)
    };

    // ScriptStruct CoreUObject.Int32Range
    // 0x0010
    struct FInt32Range
    {
        struct FInt32RangeBound LowerBound; // 0x0000(0x0008)
        struct FInt32RangeBound UpperBound; // 0x0008(0x0008)
    };

    // ScriptStruct CoreUObject.FloatInterval
    // 0x0008
    struct FFloatInterval
    {
        float Min; // 0x0000(0x0004)
        float Max; // 0x0004(0x0004)
    };

    // ScriptStruct CoreUObject.Int32Interval
    // 0x0008
    struct FInt32Interval
    {
        int Min; // 0x0000(0x0004)
        int Max; // 0x0004(0x0004)
    };

    // Class CoreUObject.Object
    // 0x0028
    class UObject
    {
    public:
        static class FUObjectArray* GObjects;

        void* Vtable; // 0x0000(0x0008)
        int32_t ObjectFlags; // 0x0008(0x0004)
        int32_t InternalIndex; // 0x000C(0x0004)
        class UClass* Class; // 0x0010(0x0008)
        struct FName Name; // 0x0018(0x0008)
        class UObject* Outer; // 0x0020(0x0008)

        static inline class TUObjectArray& GetObjects()
        {
            return GObjects->ObjObjects;
        }

        std::string GetName() const;
        std::string GetFullName() const;

        template<typename T>
        static T* FindObject(const std::string& name)
        {
            for (int32_t i = 0; i < GetObjects().Num(); ++i)
            {
                auto object = GetObjects().GetByIndex(i);

                if (object == nullptr)
                {
                    continue;
                }

                if (object->GetFullName() == name)
                {
                    return static_cast<T*>(object);
                }
            }
            return nullptr;
        }

        static class UClass* FindClass(const std::string& name)
        {
            return FindObject<class UClass>(name);
        }

        template<typename T>
        static T* GetObjectCasted(int32_t index)
        {
            return static_cast<T*>(GetObjects().GetByIndex(index));
        }

        bool IsA(class UClass* cmp) const;

        static inline void ProcessEvent(void* obj, class UFunction* function, void* parms)
        {
            auto vtable = *reinterpret_cast<void***>(obj);
            reinterpret_cast<void(*)(void*, class UFunction*, void*)>(vtable[55])(obj, function, parms);
        }
    };

    // Class CoreUObject.Interface
    // 0x0000 (0x0028 - 0x0028)
    class UInterface : public UObject
    {
    public:
    };

    // Class CoreUObject.Field
    // 0x0008 (0x0030 - 0x0028)
    class UField : public UObject
    {
    public:
        class UField* Next; // 0x0028(0x0008)
    };

    // Class CoreUObject.Struct
    // 0x0058 (0x0088 - 0x0030)
    class UStruct : public UField
    {
    public:
        class UStruct* SuperField; // 0x0030(0x0008)
        class UField* Children; // 0x0038(0x0008)
        int32_t PropertySize; // 0x0040(0x0004)
        int32_t MinAlignment; // 0x0044(0x004)
        char pad_0x0048[0x40];
    };

    // Class CoreUObject.Class
    // 0x0138 (0x01C0 - 0x0088)
    class UClass : public UStruct
    {
    public:
        char pad_0x0088[0x0138];

        template<typename T>
        inline T* CreateDefaultObject()
        {
            return static_cast<T*>(CreateDefaultObject());
        }

        template<typename Fn>
        inline Fn GetVFunction(const void* instance, std::size_t index)
        {
            auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(instance));
            return reinterpret_cast<Fn>(vtable[index]);
        }

        inline class UObject* CreateDefaultObject()
        {
            return GetVFunction<class UObject* (*)(class UClass*)>(this, 86)(this);
        }
    };

    // Class CoreUObject.Function
    // 0x0030 (0x00B8 - 0x0088)
    class UFunction : public UStruct
    {
    public:
        uint32_t FunctionFlags; // 0x0088(0x0004)
        uint8_t NumParms; // 0x008C(0x0004)
        uint16_t ParmsSize; // 0x0090(0x0004)
        uint16_t ReturnValueOffset; // 0x0094(0x0004)
        uint16_t RPCId; // 0x0098(0x0004)
        uint16_t RPCResponseId; // 0x009C(0x0004)
        class UProperty* FirstPropertyToInit; // 0x00A0(0x0008)
        class UFunction* EventGraphFunction; // 0x00A8(0x0008)
        int32_t EventGraphCallOffset; // 0x00AC(0x0004)
        void* Func; // 0x00B0(0x0008)
    };

    // Class CoreUObject.Property
    // 0x0040 (0x0070 - 0x0030)
    class UProperty : public UField
    {
    public:
        char pad_0x0030[0x0040];
    };
}
