//
// Created by fcors on 7/29/2023.
//
#include <catch2/catch_test_macros.hpp>

#include "Hero.h"
#include "Class.h"

class MockStatCurve : public RPG::StatCurve {
public:
  ~MockStatCurve() override = default;

  uint32_t getStat(uint32_t level) const override {
    return level * 2;
  }
};

TEST_CASE( "Hero Data", "[rpg-model]" ) {
  auto hero = std::make_shared<RPG::Hero>(1, "test", 3);
  REQUIRE(hero->getId() == 1);
  REQUIRE(hero->getName() == "test");
  REQUIRE(hero->getClassId() == 3);
  REQUIRE(!hero->hasStatBlock());
  CHECK_THROWS(hero->getStatBlock());

  std::map<uint8_t, std::unique_ptr<RPG::StatCurve>> curves;
  for (uint8_t i = 0; i < 8; i++) {
    curves.emplace(i, std::make_unique<MockStatCurve>());
  }
  RPG::StatBlock statBlock(std::move(curves));

  hero = std::make_shared<RPG::Hero>(2, "second", 4, std::move(statBlock));
  REQUIRE(hero->getId() == 2);
  REQUIRE(hero->getName() == "second");
  REQUIRE(hero->getClassId() == 4);
  REQUIRE(hero->hasStatBlock());

  auto &stats = hero->getStatBlock();
  REQUIRE(stats.getStat(3, 4) == 8);
  REQUIRE(stats.getStat(2, 8) == 16);
  CHECK_THROWS(stats.getStat(8, 8));

}

TEST_CASE( "Class Data", "[rpg-model]" ) {
  auto characterClass = std::make_shared<RPG::Class>(1, "test");
  REQUIRE(characterClass->getId() == 1);
  REQUIRE(characterClass->getName() == "test");


  std::map<uint8_t, std::unique_ptr<RPG::StatCurve>> curves;
  for (uint8_t i = 0; i < 8; i++) {
    curves.emplace(i, std::make_unique<MockStatCurve>());
  }
  RPG::StatBlock statBlock(std::move(curves));

  characterClass = std::make_shared<RPG::Class>(2, "second", std::move(statBlock));
  REQUIRE(characterClass->getId() == 2);
  REQUIRE(characterClass->getName() == "second");
  REQUIRE(characterClass->hasStatBlock());

  auto &stats = characterClass->getStatBlock();
  REQUIRE(stats.getStat(3, 4) == 8);
  REQUIRE(stats.getStat(2, 8) == 16);
  CHECK_THROWS(stats.getStat(8, 8));
}