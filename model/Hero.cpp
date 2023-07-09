//
// Created by fcors on 6/9/2023.
//
#include "Hero.h"

#include <stdexcept>

namespace RPG {
    Hero::Hero(size_t id, std::string_view name, size_t classId) : CoreItem(id, name), m_classId(classId)
    {
    }

    Hero::Hero(size_t id, std::string_view name, size_t classId, const StatBlock &statBlock)
        : CoreItem(id, name), m_classId(classId), m_statBlock(statBlock)
    {
    }

    Hero::Hero(size_t id, std::string_view name, size_t classId, StatBlock &&statBlock)
        : CoreItem(id, name), m_classId(classId),  m_statBlock(std::move(statBlock))
    {
    }

    Hero::~Hero() = default;

    size_t Hero::getClassId() const
    {
        return m_classId;
    }

    bool Hero::hasStatBlock() const
    {
        return m_statBlock.has_value();
    }

    const StatBlock &Hero::getStatBlock() const
    {
        if (m_statBlock.has_value())
            return m_statBlock.value();
        else
            throw std::invalid_argument(std::string("The hero ") + getName().data() + " has no stat block!");
    }
} // RPG