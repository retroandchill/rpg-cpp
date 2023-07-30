//
// Created by fcors on 7/29/2023.
//
#include <catch2/catch_test_macros.hpp>

#include "Hero.h"
#include "Class.h"

class MockStatCurve1 : public RPG::StatCurve {
  DECLARE_STAT_CURVE

public:
  explicit MockStatCurve1(uint8_t stat) : RPG::StatCurve(stat) {}
  ~MockStatCurve1() override = default;

  uint32_t calculateStatValue(uint32_t level) const override {
    return level * 2;
  }
};

IMPLEMENT_STAT_CURVE(MockStatCurve1)

class MockStatCurve2 : public RPG::StatCurve {
  DECLARE_STAT_CURVE

public:
  explicit MockStatCurve2(uint8_t stat) : RPG::StatCurve(stat) {}
  ~MockStatCurve2() override = default;

  uint32_t calculateStatValue(uint32_t level) const override {
    return getStat() * level;
  }
};

IMPLEMENT_STAT_CURVE(MockStatCurve2)

TEST_CASE( "Stat Curve Meta", "[rpg-model]") {
  auto &registry = RPG::StatRegistry::getInstance();

  CHECK_THROWS(registry.registerStatCurve("MockStatCurve1", [](uint8_t stat) { return std::make_unique<MockStatCurve1>(stat); }));

  auto statCurve = registry.createStatCurve("MockStatCurve1", 2);
  REQUIRE(statCurve->getStat() == 2);
  REQUIRE(statCurve->calculateStatValue(5) == 10);

  std::map<uint8_t, std::unique_ptr<RPG::StatCurve>> curveList;
  for (uint8_t i = 0; i < 8; i++)
    curveList.emplace(i, registry.createStatCurve("MockStatCurve2", i));

  REQUIRE(curveList[RPG::HP]->getStat() == 0);
  REQUIRE(curveList[RPG::HP]->calculateStatValue(4) == 0);

  REQUIRE(curveList[RPG::MP]->getStat() == 1);
  REQUIRE(curveList[RPG::MP]->calculateStatValue(4) == 4);

  REQUIRE(curveList[RPG::Atk]->getStat() == 2);
  REQUIRE(curveList[RPG::Atk]->calculateStatValue(4) == 8);

  REQUIRE(curveList[RPG::Def]->getStat() == 3);
  REQUIRE(curveList[RPG::Def]->calculateStatValue(4) == 12);

  REQUIRE(curveList[RPG::Mag]->getStat() == 4);
  REQUIRE(curveList[RPG::Mag]->calculateStatValue(4) == 16);

  REQUIRE(curveList[RPG::Res]->getStat() == 5);
  REQUIRE(curveList[RPG::Res]->calculateStatValue(4) == 20);

  REQUIRE(curveList[RPG::Spd]->getStat() == 6);
  REQUIRE(curveList[RPG::Spd]->calculateStatValue(4) == 24);
}

TEST_CASE( "Hero Data", "[rpg-model]" ) {
  auto hero = std::make_shared<RPG::Hero>(1, "test", 3);
  REQUIRE(hero->getId() == 1);
  REQUIRE(hero->getName() == "test");
  REQUIRE(hero->getClassId() == 3);
  REQUIRE(!hero->hasStatBlock());
  CHECK_THROWS(hero->getStatBlock());

  std::map<uint8_t, std::unique_ptr<RPG::StatCurve>> curves;
  for (uint8_t i = 0; i < 8; i++) {
    curves.emplace(i, std::make_unique<MockStatCurve1>(i));
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
    curves.emplace(i, std::make_unique<MockStatCurve1>(i));
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