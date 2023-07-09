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
    };

    class RPG_API StatBlock
    {
      public:
        uint32_t getStat(uint8_t stat, uint32_t level) const;

      private:
        std::map<uint8_t, std::unique_ptr<StatCurve>> m_stats;
    };

    class ILevelable {
      public:
        virtual bool hasStatBlock() const = 0;
        virtual const StatBlock &getStatBlock() const = 0;
    };
} // namespace RPG