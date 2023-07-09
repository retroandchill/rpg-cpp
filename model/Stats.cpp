//
// Created by fcors on 7/9/2023.
//
#include "Stats.h"

#include <stdexcept>

namespace RPG {

    uint32_t StatBlock::getStat(uint8_t stat, uint32_t level) const {
        auto findStat = m_stats.find(stat);
        if (findStat != m_stats.end())
            return findStat->second->getStat(level);
        else
            throw std::invalid_argument("The stat corresponding to id number " + std::to_string(stat) + " is invalid!");
    }
}