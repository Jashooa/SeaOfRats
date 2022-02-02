#pragma once

#include <memory>

class Config
{
    enum class BoxType : int
    {
        None,
        Box2D,
        Box3D,
    };

public:
    struct
    {
        bool enable = false;

        struct
        {
            bool enable = false;
            bool skeleton = false;
            bool name = false;
            bool health = false;
            BoxType boxType = BoxType::None;
        } player;

        struct
        {
            bool enable = false;
            bool skeleton = false;
            bool name = false;
            bool health = false;
            BoxType boxType = BoxType::None;
        } skeleton;

        struct
        {
            bool enable = false;
            bool skeleton = false;
            bool name = false;
            bool health = false;
            BoxType boxType = BoxType::None;
        } ship;

        struct
        {
            bool enable = false;
            bool skeleton = false;
            bool name = false;
            bool health = false;
            BoxType boxType = BoxType::None;
        } rowboat;

        struct
        {
            bool enable = false;
        } barrel;

        struct
        {
            bool enable = false;
            bool name = false;
            BoxType boxType = BoxType::None;
        } item;

        struct
        {
            bool enable = false;
            bool name = false;
            BoxType boxType = BoxType::None;
        } animal;

        struct
        {
            bool enable = false;
            bool skeleton = false;
            bool name = false;
            bool health = false;
        } shark;

        struct
        {
            bool enable = false;
            bool name = false;
        } mermaid;

        struct
        {
            bool enable = false;
            bool name = false;
        } shipwreck;

        struct
        {
            bool enable = false;
        } map;

        struct
        {
            bool enable = false;
        } lorebook;

        struct
        {
            bool enable = false;
        } debug;
    } esp;

    struct
    {
        bool enable = false;

        bool crosshair = true;
        bool playerList = false;
        bool compass = false;
        bool oxygen = false;
        bool waterLevel = false;
        bool anchor = false;
        bool debug = false;
    } info;

    struct
    {
        bool enable = true;

        struct
        {
            bool enable = false;
            bool player = true;
            bool skeleton = true;
        } player;

        struct
        {

        } harpoon;

        struct
        {
            bool enable = false;
            bool path = true;
        } cannon;
    } aim;
};

//inline std::unique_ptr<Config> config;
inline Config config;
