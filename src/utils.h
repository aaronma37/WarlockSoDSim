#pragma once

#include <random>

namespace utils
{
struct CastPointResult
{
  bool hit;
  double partial_resist_mod;
  bool crit;
};

inline CastPointResult nonBinaryCast(double crit_chance, double hit_chance)
{
  CastPointResult result;

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

inline double nonBinaryDamageCalculation(double lb,
                                         double ub,
                                         double spell_power,
                                         double coeff,
                                         double crit_mod,
                                         double partial_resist_mod,
                                         std::vector<double> debuff_mods)
{
  double dmg = lb + (rand() % static_cast<int>(ub - lb + 1)) + coeff * spell_power;
  dmg *= crit_mod;
  dmg *= partial_resist_mod;
  for (auto mod : debuff_mods)
    dmg *= mod;
  return dmg;
}
}  // namespace utils
