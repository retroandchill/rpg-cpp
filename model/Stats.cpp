//
// Created by fcors on 7/9/2023.
//
#include "Stats.h"

#include <stdexcept>

RPG::StatCurve::StatCurve(uint8_t stat) : m_stat(stat)
{
}

RPG::StatCurve::~StatCurve() = default;

uint8_t RPG::StatCurve::getStat() const
{
    return m_stat;
}

RPG::StatBlock::StatBlock(StatBlock::Curves &&stats) : m_stats(std::move(stats))
{
}

uint32_t RPG::StatBlock::getStat(uint8_t stat, uint32_t level) const
{
    auto findStat = m_stats.find(stat);
    if (findStat != m_stats.end())
        return findStat->second->calculateStatValue(level);
    else
        throw std::invalid_argument("The stat corresponding to id number " + std::to_string(stat) +
                                    " is invalid!");
}

RPG::ILevelable::~ILevelable() = default;

RPG::StatRegistry::StatRegistry() = default;

RPG::StatRegistry &RPG::StatRegistry::getInstance()
{
    static StatRegistry registry;
    return registry;
}

std::string_view RPG::StatRegistry::registerStatCurve(std::string_view key, const RPG::StatRegistry::CurveCreator &creator)
{
    auto [it, inserted] = m_registeredCurves.try_emplace(std::string(key), creator);
    if (inserted)
        return it->first;
    else
        throw std::invalid_argument(std::string("The stat curve class ") + key.data() + " has already been registered!");
}

std::unique_ptr<RPG::StatCurve> RPG::StatRegistry::createStatCurve(std::string_view key,
                                                                   uint8_t stat) const
{
    if (auto findCreator = m_registeredCurves.find(key);findCreator != m_registeredCurves.end())
        return findCreator->second(stat);
    else
        throw std::invalid_argument(std::string("The stat curve has not been registered ") + key.data() + " has already been registered!");
}
