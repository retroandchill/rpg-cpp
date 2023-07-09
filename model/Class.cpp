//
// Created by fcors on 7/9/2023.
//
#include "Class.h"

#include <stdexcept>

RPG::Class::Class(size_t id, std::string_view name) : CoreItem(id, name)
{
}

RPG::Class::Class(size_t id, std::string_view name, RPG::StatBlock &&statBlock) : CoreItem(id, name), m_statBlock(std::move(statBlock))
{
}

RPG::Class::~Class() = default;

bool RPG::Class::hasStatBlock() const
{
    return m_statBlock.has_value();
}

const RPG::StatBlock &RPG::Class::getStatBlock() const
{
    if (m_statBlock.has_value())
        return m_statBlock.value();
    else
        throw std::invalid_argument(std::string("The class ") + getName().data() + " has no stat block!");
}
