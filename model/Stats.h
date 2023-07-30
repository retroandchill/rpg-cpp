//
// Created by fcors on 7/9/2023.
//
#pragma once

#include "RPG_global.h"

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <functional>

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
        explicit StatCurve(uint8_t stat);
        virtual ~StatCurve() = 0;

        virtual std::string_view getClassName() const = 0;
        uint8_t getStat() const;
        virtual uint32_t calculateStatValue(uint32_t level) const = 0;

      private:
        uint8_t m_stat;
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

    class RPG_API StatRegistry {
      private:
        StatRegistry();

      public:
        using CurveCreator = std::function<std::unique_ptr<StatCurve>(uint8_t)>;

        static StatRegistry &getInstance();

        std::string_view registerStatCurve(std::string_view key, const CurveCreator &creator);
        std::unique_ptr<RPG::StatCurve> createStatCurve(std::string_view key, uint8_t stat) const;

      private:
        std::map<std::string, CurveCreator, std::less<>> m_registeredCurves;
    };
} // namespace RPG

#define DECLARE_STAT_CURVE private: static std::string_view s_className; public: std::string_view getClassName() const override; private:
#define IMPLEMENT_STAT_CURVE(Curve) std::string_view Curve::s_className = RPG::StatRegistry::getInstance().registerStatCurve(#Curve, [](uint8_t stat) { return std::make_unique<Curve>(stat); }); std::string_view Curve::getClassName() const { return s_className; }