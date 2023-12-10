#pragma once
#include <state.h>

#include <random>

namespace utils
{
enum class SpellSchool
{
  SHADOW,
  FIRE,
};

enum class Specialization
{
  DESTRUCTION,
  AFFLICTION,
  DEMONOLOGY,
  NONE,
};

struct CastPointResult
{
  bool hit;
  double partial_resist_mod;
  bool crit;
};

inline CastPointResult nonBinaryCast(double crit_chance, double hit_chance, SpellSchool school,
                                     Specialization specialization, const state::Talents& talents,
                                     const state::Runes& runes)
{
  CastPointResult result;

  if (specialization == Specialization::AFFLICTION)
    hit_chance += .02 * talents.suppression;

  if (specialization == Specialization::DESTRUCTION)
    crit_chance += .01 * talents.devastation;

  crit_chance += runes.demonic_tactics;

  result.hit = (((double)rand() / (RAND_MAX)) <= hit_chance);
  result.crit = (((double)rand() / (RAND_MAX)) <= crit_chance);
  auto partial_roll = ((double)rand() / (RAND_MAX));
  if (partial_roll <= .63)
    result.partial_resist_mod = 1.0;
  else if (partial_roll <= 90)
    result.partial_resist_mod = .75;
  else if (partial_roll <= 99)
    result.partial_resist_mod = .5;
  else
    result.partial_resist_mod = .25;
  return result;
}

inline double nonBinaryDamageCalculation(CastPointResult& result, double lb, double ub, double spell_power,
                                         SpellSchool school, Specialization specialization, double coeff,
                                         const state::Talents& talents, state::Debuffs& debuffs)
{
  double dmg = lb + (rand() % static_cast<int>(ub - lb + 1)) + coeff * spell_power;

  double crit_mod = 1.0;
  if (result.crit)
  {
    if (talents.ruin && specialization == Specialization::DESTRUCTION)
      crit_mod = 2.0;
    else
      crit_mod = 1.5;
  }

  dmg *= crit_mod;
  dmg *= result.partial_resist_mod;

  if (talents.demonic_sacrifice == state::Talents::DSType::SUCCUBUS && school == SpellSchool::SHADOW)
    dmg *= 1.15;

  if (talents.demonic_sacrifice == state::Talents::DSType::IMP && school == SpellSchool::FIRE)
    dmg *= 1.15;

  if (talents.master_demonologist == state::Talents::MDType::SUCCUBUS)
    dmg *= 1.10;

  if (school == SpellSchool::SHADOW)
  {
    dmg *= (1.0 + talents.shadow_mastery * .02);
    dmg *= (1.0 + debuffs.shadow_vulnerability * .03);
  }

  return dmg;
}
}  // namespace utils
