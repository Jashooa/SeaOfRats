#pragma once

#include <Windows.h>

#include <codecvt>
#include <locale>
#include <string>
#include <unordered_set>

namespace SDK
{
    // 0x0010
    class FUObjectItem
    {
    public:
        enum class EInternalObjectFlags : int32_t
        {
            None = 0,
            Native = 1 << 25,
            Async = 1 << 26,
            AsyncLoading = 1 << 27,
            Unreachable = 1 << 28,
            PendingKill = 1 << 29,
            RootSet = 1 << 30,
            NoStrongReference = 1 << 31
        };

        class UObject* Object; // 0x0000(0x0008)
        int32_t Flags; // 0x0008(0x0004)
        int32_t ClusterIndex; // 0x000C(0x0004)
        int32_t SerialNumber; // 0x0010(0x0004)

        inline bool IsUnreachable() const
        {
            return !!(Flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::Unreachable));
        }

        inline bool IsPendingKill() const
        {
            return !!(Flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::PendingKill));
        }
    };

    // 0x0010
    class TUObjectArray
    {
    public:
        inline int32_t Num() const
        {
            return NumElements;
        }

        inline UObject* GetByIndex(int32_t index) const
        {
            return Objects[index].Object;
        }

        inline FUObjectItem* GetItemByIndex(int32_t index) const
        {
            if (index < NumElements)
            {
                return &Objects[index];
            }
            return nullptr;
        }

    private:
        class FUObjectItem* Objects; // 0x0000(0x0008)
        int32_t MaxElements; // 0x0008(0x0004)
        int32_t NumElements; // 0x000C(0x0004)
    };

    // 0x0020
    class FUObjectArray
    {
    public:
        int32_t ObjFirstGCIndex; // 0x0000(0x0004)
        int32_t ObjLastNonGCIndex; // 0x0004(0x0004)
        int32_t MaxObjectsNotConsideredByGC; // 0x0008(0x0004)
        int32_t OpenForDisregardForGC; // 0x000C(0x0004)
        class TUObjectArray ObjObjects; // 0x0010(0x0010)
    };

    // 0x0010
    template<class T>
    class TArray
    {
        friend class FString;

    public:
        inline TArray()
        {
            Data = nullptr;
            ArrayNum = ArrayMax = 0;
        }

        inline int32_t Num() const
        {
            return ArrayNum;
        }

        inline T& operator[](int32_t i)
        {
            return Data[i];
        }

        inline const T& operator[](int32_t i) const
        {
            return Data[i];
        }

        inline T* begin()
        {
            return Data;
        }

        inline T* end()
        {
            return Data + ArrayNum;
        }

        inline const T* begin() const
        {
            return Data;
        }

        inline const T* end() const
        {
            return Data + ArrayNum;
        }

        inline bool IsValidIndex(int32_t i) const
        {
            return i >= 0 && i < ArrayNum;
        }

        inline void Push(T item)
        {
            if (ArrayNum == ArrayMax)
            {
                int32_t newMax = 0;
                if (ArrayMax == 0)
                {
                    newMax++;
                }
                else
                {
                    newMax = ArrayMax * 2;
                }
                T* newData = new T[newMax];

                for (int32_t i = 0; i < ArrayMax; ++i)
                {
                    newData[i] = Data[i];
                }

                delete[] Data;
                ArrayMax = newMax;
                Data = newData;
            }

            Data[ArrayNum] = item;
            ArrayNum++;
        }

    private:
        T* Data; // 0x0000(0x0008)
        int32_t ArrayNum; // 0x0008(0x0004)
        int32_t ArrayMax; // 0x000C(0x0004)
    };

    // 0x0410
    class FNameEntry
    {
    public:
        #define NAME_WIDE_MASK 0x1
        #define NAME_INDEX_SHIFT 1

        int32_t Index; // 0x0000(0x0004)
        char pad_0x0004[0x0004];
        class FNameEntry* HashNext; // 0x0008(0x0008)
        union // 0x0010(0x0400)
        {
            char AnsiName[1024];
            wchar_t WideName[1024];
        };

        inline const int32_t GetIndex() const
        {
            return Index >> NAME_INDEX_SHIFT;
        }

        inline bool IsWide() const
        {
            return (Index & NAME_WIDE_MASK);
        }

        inline const char* GetAnsiName() const
        {
            return AnsiName;
        }

        inline const wchar_t* GetWideName() const
        {
            return WideName;
        }
    };

    // 0x0010
    template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
    class TStaticIndirectArrayThreadSafeRead
    {
    public:
        inline int32_t Num() const
        {
            return NumElements;
        }

        inline bool IsValidIndex(int32_t index) const
        {
            return index < Num() && index >= 0;
        }

        inline ElementType const* const& operator[](int32_t index) const
        {
            return *GetItemPtr(index);
        }

    private:
        enum
        {
            ChunkTableSize = (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk
        };

        ElementType** Chunks[ChunkTableSize]; // 0x0000(0x0008)
        int32_t NumElements; // 0x0008(0x0004)
        int32_t NumChunks; // 0x000C(0x0004)

        inline ElementType const* const* GetItemPtr(int32_t Index) const
        {
            const auto ChunkIndex = Index / ElementsPerChunk;
            const auto WithinChunkIndex = Index % ElementsPerChunk;
            const auto Chunk = Chunks[ChunkIndex];
            return Chunk + WithinChunkIndex;
        }
    };

    using TNameEntryArray = TStaticIndirectArrayThreadSafeRead<FNameEntry, 2 * 1024 * 1024, 16384>;

    // 0x0008
    struct FName
    {
        int32_t ComparisonIndex; // 0x0000(0x0004)
        int32_t Number; // 0x0004(0x0004)

        inline FName() : ComparisonIndex(0), Number(0)
        {
        }

        inline FName(int32_t i) : ComparisonIndex(i), Number(0)
        {
        }

        FName(const char* nameToFind) : ComparisonIndex(0), Number(0)
        {
            static std::unordered_set<int> cache;

            for (auto i : cache)
            {
                if (!std::strcmp(GetNames()[i]->GetAnsiName(), nameToFind))
                {
                    ComparisonIndex = i;

                    return;
                }
            }

            for (int32_t i = 0; i < GetNames().Num(); ++i)
            {
                if (GetNames()[i] != nullptr)
                {
                    if (!std::strcmp(GetNames()[i]->GetAnsiName(), nameToFind))
                    {
                        cache.insert(i);

                        ComparisonIndex = i;

                        return;
                    }
                }
            }
        }

        static TNameEntryArray* GNames;
        static inline TNameEntryArray& GetNames()
        {
            return *GNames;
        }

        inline bool IsValid()
        {
            return ComparisonIndex >= 0 && ComparisonIndex < GetNames().Num();
        }

        inline const auto GetName() const
        {
            auto nameEntry = GetNames()[ComparisonIndex];
            if (!nameEntry)
            {
                return std::string{};
            }
            return std::string{ nameEntry->GetAnsiName() };
        }

        inline bool operator==(const FName& other) const
        {
            return ComparisonIndex == other.ComparisonIndex;
        }
    };

    // 0x0010
    class FString : public TArray<wchar_t>
    {
    public:
        inline FString()
        {
        }

        FString(const wchar_t* other)
        {
            ArrayMax = ArrayNum = *other ? static_cast<int32_t>(std::wcslen(other)) + 1 : 0;

            if (ArrayNum)
            {
                Data = const_cast<wchar_t*>(other);
            }
        }

        inline bool IsValid() const
        {
            return Data != nullptr;
        }

        inline bool IsEmpty() const
        {
            return Num() <= 1;
        }

        inline const wchar_t* c_str() const
        {
            return Data;
        }

        auto ToString() const
        {
            /*const auto length = std::wcslen(Data);
            std::string str(length, '\0');
            std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);*/

            const int length = WideCharToMultiByte(CP_UTF8, 0, Data, -1, NULL, 0, NULL, NULL);
            char* buffer = new char[length];
            int bytesWritten = WideCharToMultiByte(CP_UTF8, 0, Data, -1, buffer, length, NULL, NULL);

            if (bytesWritten)
            {
                return std::string(buffer);
            }
            else
            {
                return std::string();
            }
        }
    };

    // 0x0001
    template<class TEnum>
    class TEnumAsByte
    {
    public:
        inline TEnumAsByte()
        {
        }

        inline TEnumAsByte(TEnum _value) : value(static_cast<uint8_t>(_value))
        {
        }

        explicit inline TEnumAsByte(int32_t _value) : value(static_cast<uint8_t>(_value))
        {
        }

        explicit inline TEnumAsByte(uint8_t _value) : value(_value)
        {
        }

        inline operator TEnum() const
        {
            return (TEnum) value;
        }

        inline TEnum GetValue() const
        {
            return (TEnum) value;
        }

    private:
        uint8_t value; // 0x0000(0x0001)
    };

    // 0x0010
    class FScriptInterface
    {
    public:
        inline class UObject* GetObject() const
        {
            return ObjectPointer;
        }

        inline class UObject*& GetObjectRef()
        {
            return ObjectPointer;
        }

        inline void* GetInterface() const
        {
            return ObjectPointer != nullptr ? InterfacePointer : nullptr;
        }

    private:
        class UObject* ObjectPointer; // 0x0000(0x0008)
        void* InterfacePointer; // 0x0008(0x0008)
    };

    // 0x0000 (0x0010 - 0x0010)
    template<class InterfaceType>
    class TScriptInterface : public FScriptInterface
    {
    public:
        inline InterfaceType* operator->() const
        {
            return static_cast<InterfaceType*>(GetInterface());
        }

        inline InterfaceType& operator*() const
        {
            return *static_cast<InterfaceType*>(GetInterface());
        }

        inline operator bool() const
        {
            return GetInterface() != nullptr;
        }
    };

    // 0x0038
    struct FText
    {
    public:
        class FString* DisplayString; // 0x0000(0x008)
        char pad_0x0008[0x0030];
    };

    // 0x0008
    struct FWeakObjectPtr
    {
    public:
        int32_t ObjectIndex; // 0x0000(0x0004)
        int32_t ObjectSerialNumber; // 0x0004(0x0004)

        inline bool SerialNumbersMatch(FUObjectItem* ObjectItem) const
        {
            return ObjectItem->SerialNumber == ObjectSerialNumber;
        }

        bool IsValid() const;
        class UObject* Get() const;
    };

    // 0x0000 (0x0008 - 0x0008)
    template<class T, class TWeakObjectPtrBase = FWeakObjectPtr>
    struct TWeakObjectPtr : private TWeakObjectPtrBase
    {
    public:
        inline T* Get() const
        {
            return (T*) TWeakObjectPtrBase::Get();
        }

        inline T& operator*() const
        {
            return *Get();
        }

        inline T* operator->() const
        {
            return Get();
        }

        inline bool IsValid() const
        {
            return TWeakObjectPtrBase::IsValid();
        }
    };
}
