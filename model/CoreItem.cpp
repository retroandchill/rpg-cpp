//
// Created by fcors on 6/9/2023.
//
#include "CoreItem.h"

RPG::CoreItem::CoreItem(size_t id, std::string_view name) : m_id(id), m_name(name)
{
}

RPG::CoreItem::~CoreItem() = default;

size_t RPG::CoreItem::getId() const
{
    return m_id;
}

std::string_view RPG::CoreItem::getName() const
{
    return m_name;
}