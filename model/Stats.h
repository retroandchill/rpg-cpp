//
// Created by fcors on 7/9/2023.
//
#pragma once

#include "RPG_global.h"

#include <cstdint>
#include <map>
#include <memory>

namespace RPG
{

    constexpr uint8_t HP = 0;
    constexpr uint8_t MP = 1;
    constexpr uint8_t Atk = 2;
    constexpr uint8_t Def = 3;
    constexpr uint8_t Mag = 4;
    constexpr uint8_t Res = 5;
    constexpr uint8_t Spd = 6;

    class RPG_API StatCurve
    {
      public:
        virtual ~StatCurve() = 0;
        virtual uint32_t getStat(uint32_t level) const = 0;
    };

    class RPG_API StatBlock
    {
      public:
        using Curves = std::map<uint8_t, std::unique_ptr<StatCurve>>;

        explicit StatBlock(Curves &&stats);
        StatBlock(const StatBlock &other) = delete;
        StatBlock(StatBlock &&other) = default;
        StatBlock &operator=(const StatBlock &other) = delete;
        StatBlock &operator=(StatBlock &&other) = default;

        uint32_t getStat(uint8_t stat, uint32_t level) const;

      private:
        Curves m_stats;
    };

    class ILevelable
    {
      public:
        virtual ~ILevelable() = 0;
        virtual bool hasStatBlock() const = 0;
        virtual const StatBlock &getStatBlock() const = 0;
    };
} // namespace RPG