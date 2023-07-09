//
// Created by fcors on 6/9/2023.
//
#include "Hero.h"

#include <stdexcept>

RPG::Hero::Hero(size_t id, std::string_view name, size_t classId)
    : CoreItem(id, name), m_classId(classId)
{
}

RPG::Hero::Hero(size_t id, std::string_view name, size_t classId, StatBlock &&statBlock)
    : CoreItem(id, name), m_classId(classId), m_statBlock(std::move(statBlock))
{
}

RPG::Hero::~Hero() = default;

size_t RPG::Hero::getClassId() const
{
    return m_classId;
}

bool RPG::Hero::hasStatBlock() const
{
    return m_statBlock.has_value();
}

const RPG::StatBlock &RPG::Hero::getStatBlock() const
{
    if (m_statBlock.has_value())
        return m_statBlock.value();
    else
        throw std::invalid_argument(std::string("The hero ") + getName().data() +
                                    " has no stat block!");
}