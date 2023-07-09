//
// Created by fcors on 7/9/2023.
//
#pragma once

#include "CoreItem.h"
#include "Stats.h"

#include <optional>

namespace RPG
{
    class RPG_API Class : public CoreItem, public ILevelable
    {
      public:
        Class(size_t id, std::string_view name);
        Class(size_t id, std::string_view name, const StatBlock &statBlock);
        Class(size_t id, std::string_view name, StatBlock &&statBlock);

        bool hasStatBlock() const final;
        const StatBlock &getStatBlock() const final;

      private:
        std::optional<StatBlock> m_statBlock;
    };
}
