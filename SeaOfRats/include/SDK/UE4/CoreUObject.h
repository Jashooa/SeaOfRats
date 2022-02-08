#pragma once

#include <string>

#include "Basic.h"

namespace SDK
{
    // Class CoreUObject.Object
    // 0x0028
    class UObject
    {
    public:
        static class FUObjectArray* GObjects;
        void* Vtable;
        int32_t ObjectFlags;
        int32_t InternalIndex;
        class UClass* Class;
        struct FName Name;
        class UObject* Outer;

        static inline class TUObjectArray& GetObjects()
        {
            return GObjects->ObjObjects;
        }

        std::string GetName() const;

        std::string GetFullName() const;

        template<typename T>
        static T* FindObject(const std::string& name)
        {
            for (int i = 0; i < GetObjects().Num(); ++i)
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
        static T* GetObjectCasted(std::size_t index)
        {
            return static_cast<T*>(GetObjects().GetByIndex(index));
        }

        bool IsA(class UClass* cmp) const;

        static inline void ProcessEvent(void* obj, class UFunction* function, void* parms)
        {
            auto vtable = *reinterpret_cast<void***>(obj);
            reinterpret_cast<void(*)(void*, class UFunction*, void*)>(vtable[59])(obj, function, parms);
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
        class UField* Next;
    };

    // Class CoreUObject.Struct
    // 0x0058 (0x0088 - 0x0030)
    class UStruct : public UField
    {
    public:
        class UStruct* SuperField;
        class UField* Children;
        int32_t PropertySize;
        int32_t MinAlignment;
        unsigned char UnknownData00[0x40];
    };

    // Class CoreUObject.Class
    // 0x0138 (0x01C0 - 0x0088)
    class UClass : public UStruct
    {
    public:
        unsigned char UnknownData00[0x138]; // 0x0088(0x0138)

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
            return GetVFunction<class UObject* (*)(class UClass*)>(this, 91)(this);
        }
    };

    // Class CoreUObject.Property
    // 0x0040 (0x0070 - 0x0030)
    class UProperty : public UField
    {
    public:
        unsigned char UnknownData00[0x40]; // 0x0030(0x0040)
    };

    // Class CoreUObject.Function
    // 0x0030 (0x00B8 - 0x0088)
    class UFunction : public UStruct
    {
    public:
        int32_t FunctionFlags;
        int16_t RepOffset;
        int8_t NumParms;
        int16_t ParmsSize;
        int16_t ReturnValueOffset;
        int16_t RPCId;
        int16_t RPCResponseId;
        UProperty* FirstPropertyToInit;
        UFunction* EventGraphFunction;
        int32_t EventGraphCallOffset;
        void* Func;
    };

    // ScriptStruct CoreUObject.StringAssetReference
    // 0x0010
    struct FStringAssetReference
    {
        class FString AssetLongPathname; // 0x0000(0x0010)
    };
}
