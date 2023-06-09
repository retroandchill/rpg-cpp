//
// Created by fcors on 6/9/2023.
//

#pragma once

#include <string>

namespace RPG {

    class CoreItem {
    public:
        CoreItem(size_t id, std::string_view name);
        virtual ~CoreItem();

    private:
        size_t m_id;
        std::string m_name;

    };

} // RPG
