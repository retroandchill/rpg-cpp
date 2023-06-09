//
// Created by fcors on 6/9/2023.
//

#include "CoreItem.h"

namespace RPG {
    CoreItem::CoreItem(size_t id, std::string_view name) : m_id(id), m_name(name) {

    }

    CoreItem::~CoreItem() = default;


} // RPG