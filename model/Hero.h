//
// Created by fcors on 6/9/2023.
//
#pragma once

#include "CoreItem.h"
#include "Stats.h"

#include <optional>

namespace RPG
{

    class RPG_API Hero : public CoreItem, public ILevelable
    {
      public:
        Hero(size_t id, std::string_view name, size_t classId);
        Hero(size_t id, std::string_view name, size_t classId, const StatBlock &statBlock);
        Hero(size_t id, std::string_view name, size_t classId, StatBlock &&statBlock);
        ~Hero() override;

        size_t getClassId() const;
        bool hasStatBlock() const final;
        const StatBlock &getStatBlock() const final;


      private:
        size_t m_classId;
        std::optional<StatBlock> m_statBlock;
    };

} // namespace RPG
