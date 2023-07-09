//
// Created by fcors on 7/9/2023.
//
#include "Stats.h"

#include <stdexcept>

namespace RPG
{

    StatBlock::StatBlock(const StatBlock::Curves &stats)
    {
        for (auto &[id, curve] : stats)
            m_stats.try_emplace(id, curve->clone());
    }

    StatBlock::StatBlock(StatBlock::Curves &&stats) : m_stats(std::move(stats))
    {
    }

    StatBlock::StatBlock(const StatBlock &other) noexcept
    {
        for (auto &[id, curve] : other.m_stats)
            m_stats.try_emplace(id, curve->clone());
    }

    StatBlock::StatBlock(StatBlock &&other) noexcept = default;

    StatBlock::~StatBlock()
    = default;

    StatBlock &StatBlock::operator=(const StatBlock &other) noexcept
    {
        for (auto &[id, curve] : other.m_stats)
            m_stats.try_emplace(id, curve->clone());

        return *this;
    }

    StatBlock &StatBlock::operator=(StatBlock &&other) noexcept = default;

    uint32_t StatBlock::getStat(uint8_t stat, uint32_t level) const
    {
        auto findStat = m_stats.find(stat);
        if (findStat != m_stats.end())
            return findStat->second->getStat(level);
        else
            throw std::invalid_argument("The stat corresponding to id number " +
                                        std::to_string(stat) + " is invalid!");
    }

    ILevelable::~ILevelable() = default;
} // namespace RPG