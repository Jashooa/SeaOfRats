#pragma once

#include <memory>

class Config
{
public:
    struct
    {
        bool enable = false;

        struct
        {
            bool enable = false;
            bool bones = false;
            bool name = false;
            bool health = false;
        } player;

        struct
        {
            bool enable = false;
            bool health = false;
        } skeleton;

        struct
        {
            bool enable = false;
        } npc;

        struct
        {
            bool enable = false;
            bool name = false;
            bool health = false;
        } ship;

        struct
        {
            bool enable = false;
        } rowboat;

        struct
        {
            bool enable = false;
        } ghostship;

        struct
        {
            bool enable = false;
        } barrel;

        struct
        {
            bool enable = false;
            bool name = false;
        } item;

        struct
        {
            bool enable = false;
            bool name = false;
        } animal;

        struct
        {
            bool enable = false;
            bool name = false;
            bool health = false;
        } shark;

        struct
        {
            bool enable = false;
            bool name = false;
            bool health = false;
        } megalodon;

        struct
        {
            bool enable = false;
            bool name = false;
            bool health = false;
        } siren;

        struct
        {
            bool enable = false;
            bool name = false;
            bool health = false;
        } kraken;

        struct
        {
            bool enable = false;
            bool name = false;
        } mermaid;

        struct
        {
            bool enable = false;
            bool name = false;
        } island;

        struct
        {
            bool enable = false;
            bool name = false;
        } shipwreck;

        struct
        {
            bool enable = false;
        } mappin;

        struct
        {
            bool enable = false;
        } lorebook;

        struct
        {
            bool enable = false;
        } treasuremap;

        struct
        {
            bool enable = false;
        } enchantedcompass;

        struct
        {
            bool enable = false;
        } storm;

        struct
        {
            bool enable = false;
        } skeletonthrone;

        struct
        {
            bool enable = false;
        } event;

        struct
        {
            bool enable = false;
        } trigger;
    } esp;

    struct
    {
        bool enable = false;

        bool crosshair = true;
        bool playerList = true;
        bool compass = false;
        bool oxygen = false;
        bool waterLevel = false;
        bool anchor = false;
        bool debug = false;
    } info;

    struct
    {
        bool enable = false;

        bool antiafk = false;
    } client;

    struct
    {
        bool enable = true;

        struct
        {
            bool enable = false;
            bool player = true;
            bool skeleton = true;
        } weapon;

        struct
        {
            bool enable = false;
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
