#pragma once

#include <Windows.h>

#include <codecvt>
#include <locale>
#include <string>
#include <unordered_set>

namespace SDK
{
    class UObject;

    class FUObjectItem
    {
    public:
        UObject* Object;
        int32_t Flags;
        int32_t ClusterIndex;
        int32_t SerialNumber;

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

        inline bool IsUnreachable() const
        {
            return !!(Flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::Unreachable));
        }

        inline bool IsPendingKill() const
        {
            return !!(Flags & static_cast<std::underlying_type_t<EInternalObjectFlags>>(EInternalObjectFlags::PendingKill));
        }
    };

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
        FUObjectItem* Objects;
        int32_t MaxElements;
        int32_t NumElements;
    };

    class FUObjectArray
    {
    public:
        int32_t ObjFirstGCIndex;
        int32_t ObjLastNonGCIndex;
        int32_t MaxObjectsNotConsideredByGC;
        int32_t OpenForDisregardForGC;
        TUObjectArray ObjObjects;
    };

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

        inline int Num() const
        {
            return ArrayNum;
        }

        inline T& operator[](int i)
        {
            return Data[i];
        }

        inline const T& operator[](int i) const
        {
            return Data[i];
        }

        inline bool IsValidIndex(int i) const
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
        T* Data;
        int32_t ArrayNum;
        int32_t ArrayMax;
    };

    class FNameEntry
    {
    public:
        static const auto NAME_WIDE_MASK = 0x1;
        static const auto NAME_INDEX_SHIFT = 1;

        int32_t Index;
        char UnknownData00[0x04];
        FNameEntry* HashNext;
        union
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

    template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
    class TStaticIndirectArrayThreadSafeRead
    {
    public:
        inline size_t Num() const
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
        inline ElementType const* const* GetItemPtr(int32_t Index) const
        {
            const auto ChunkIndex = Index / ElementsPerChunk;
            const auto WithinChunkIndex = Index % ElementsPerChunk;
            const auto Chunk = Chunks[ChunkIndex];
            return Chunk + WithinChunkIndex;
        }

        enum
        {
            ChunkTableSize = (MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk
        };

        ElementType** Chunks[ChunkTableSize];
        int32_t NumElements;
        int32_t NumChunks;
    };

    using TNameEntryArray = TStaticIndirectArrayThreadSafeRead<FNameEntry, 2 * 1024 * 1024, 16384>;

    struct FName
    {
        int32_t ComparisonIndex;
        int32_t Number;

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

            for (auto i = 0; i < GetNames().Num(); ++i)
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

        inline const char* GetName() const
        {
            auto nameEntry = GetNames()[ComparisonIndex];
            if (!nameEntry)
            {
                return nullptr;
            }
            return nameEntry->GetAnsiName();
        }

        inline bool operator==(const FName& other) const
        {
            return ComparisonIndex == other.ComparisonIndex;
        }
    };

    class FString : public TArray<wchar_t>
    {
    public:
        inline FString()
        {
        }

        FString(const wchar_t* other)
        {
            ArrayMax = ArrayNum = *other ? static_cast<int>(std::wcslen(other)) + 1 : 0;

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

        std::string ToString() const
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
        uint8_t value;
    };

    class FScriptInterface
    {
    private:
        UObject* ObjectPointer;
        void* InterfacePointer;

    public:
        inline UObject* GetObject() const
        {
            return ObjectPointer;
        }

        inline UObject*& GetObjectRef()
        {
            return ObjectPointer;
        }

        inline void* GetInterface() const
        {
            return ObjectPointer != nullptr ? InterfacePointer : nullptr;
        }
    };

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

    struct FText
    {
        char UnknownData00[0x38];
    };

    struct FWeakObjectPtr
    {
    public:
        inline bool SerialNumbersMatch(FUObjectItem* ObjectItem) const
        {
            return ObjectItem->SerialNumber == ObjectSerialNumber;
        }

        bool IsValid() const;

        UObject* Get() const;

        int32_t ObjectIndex;
        int32_t ObjectSerialNumber;
    };

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
