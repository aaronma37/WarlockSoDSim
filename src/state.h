#pragma once

#include <policy_ids.h>

#include <iostream>
#include <string>
#include <unordered_map>

namespace state
{
struct Talents
{
  bool improved_shadow_bolt = true;
  bool ruin = true;
  double nightfall_proc = 0.04;
};

struct Caster
{
  policies::PolicyID policy_id;
  Talents talents;

  // Dynamic stats
  double crit_chance = .3;
  double hit_chance = .95;
  int spell_power = 50;
  bool nightfall = false;
};

struct Debuffs
{
  bool isb = false;
  int isb_charges = 0;
  double isb_mod = 1.0;
  void* isb_addr = 0;

  std::unordered_map<std::string, double> corruption_ids;
};

struct State
{
  std::unordered_map<std::string, Caster> casters;

  // Debuffs
  Debuffs debuffs;

  // Results
  int damage_dealt = 0;
  double time = 0;
  double dps = 0;

  friend std::ostream& operator<<(std::ostream& os, const state::State& state);
};

inline std::ostream& operator<<(std::ostream& os, const state::State& state)
{
  os << "\n---Summary---\n";
  os << "Damage dealt: " << state.damage_dealt << "\n";
  os << "DPS: " << state.dps << "\n";
  return os;
}

inline void postProcess(State& state)
{
  state.dps = state.damage_dealt / state.time;
}
}  // namespace state
