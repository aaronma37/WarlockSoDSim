#pragma once

#include <utils.h>

#include <unordered_map>

namespace spells
{
struct Shadowbolt
{
  Shadowbolt();
  static constexpr double coefficient = 3 / 3.5;
  static constexpr utils::SpellSchool spell_school = utils::SpellSchool::SHADOW;
  static constexpr utils::Specialization specialization = utils::Specialization::DESTRUCTION;
  static std::unordered_map<int, int> min;
  static std::unordered_map<int, int> max;
  static std::unordered_map<int, double> cast_time;
};

struct Corruption
{
  Corruption();
  static constexpr double coefficient = 1.0;
  static constexpr utils::SpellSchool spell_school = utils::SpellSchool::SHADOW;
  static constexpr utils::Specialization specialization = utils::Specialization::AFFLICTION;
  static std::unordered_map<int, int> tick_dmg;
  static std::unordered_map<int, double> cast_time;
};
}  // namespace spells
