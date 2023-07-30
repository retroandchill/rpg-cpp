//
// Created by fcors on 7/30/2023.
//
#pragma once

#include "CoreItem.h"

#include <map>
#include <vector>

namespace RPG
{

    constexpr uint8_t EQUIP_WEAPON = 0;
    constexpr uint8_t EQUIP_SHIELD = 1;
    constexpr uint8_t EQUIP_HELM = 2;
    constexpr uint8_t EQUIP_ARMOR = 3;
    constexpr uint8_t EQUIP_ACCESSORY = 4;

    class RPG_API Equipable : public RPG::CoreItem
    {
      public:
        Equipable(size_t id, std::string_view name, std::map<uint8_t, int32_t> &&statChanges);

        virtual uint8_t getType() const = 0;

      private:
        std::map<uint8_t, int32_t> m_statChanges;
    };

    using EquipmentList = std::vector<std::pair<uint8_t, uint8_t>>;

} // namespace RPG
