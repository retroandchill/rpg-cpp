//
// Created by fcors on 7/30/2023.
//

#include "Equipable.h"

namespace RPG
{
    Equipable::Equipable(size_t id, std::string_view name, std::map<uint8_t, int32_t> &&statChanges) : RPG::CoreItem(id, name), m_statChanges(std::move(statChanges))
    {
    }
} // namespace RPG