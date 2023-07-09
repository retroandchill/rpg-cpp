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
    enum class Stat : uint8_t
    {
        HP = 0,
        MP = 1,
        Atk = 2,
        Def = 3,
        Mag = 4,
        Res = 5,
        Spd = 6
    };

    class StatCurve
    {
      public:
        virtual ~StatCurve() = 0;
        virtual uint32_t getStat(uint32_t level) const = 0;
        virtual std::unique_ptr<StatCurve> clone() const = 0;
    };

    class RPG_API StatBlock
    {
      public:
        using Curves = std::map<uint8_t, std::unique_ptr<StatCurve>>;

        explicit StatBlock(const Curves &stats);
        explicit StatBlock(Curves &&stats);
        StatBlock(const StatBlock &other) noexcept;
        StatBlock(StatBlock &&other) noexcept;
        virtual ~StatBlock();

        StatBlock &operator=(const StatBlock &other) noexcept;
        StatBlock &operator=(StatBlock &&other) noexcept;

        uint32_t getStat(uint8_t stat, uint32_t level) const;

      private:
        Curves m_stats;
    };

    class ILevelable {
      public:
        virtual ~ILevelable() = 0;
        virtual bool hasStatBlock() const = 0;
        virtual const StatBlock &getStatBlock() const = 0;
    };
} // namespace RPG