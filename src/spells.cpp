
#include <spells.h>

namespace spells
{
// Initialize Shadowbolt
Shadowbolt::Shadowbolt()
{
  min[1] = 13;
  min[2] = 26;
  min[3] = 52;
  min[4] = 92;
  min[5] = 150;
  min[6] = 213;
  min[7] = 292;
  min[8] = 373;
  min[9] = 455;
  min[10] = 482;

  max[1] = 18;
  max[2] = 32;
  max[3] = 61;
  max[4] = 104;
  max[5] = 170;
  max[6] = 240;
  max[7] = 327;
  max[8] = 415;
  max[9] = 507;
  max[10] = 538;

  cast_time[1] = 1.7;
  cast_time[2] = 2.2;
  cast_time[3] = 2.8;
  cast_time[4] = 3.0;
  cast_time[5] = 3.0;
  cast_time[6] = 3.0;
  cast_time[7] = 3.0;
  cast_time[8] = 3.0;
  cast_time[9] = 3.0;
  cast_time[10] = 3.0;

  mana_cost[1] = 25;
  mana_cost[2] = 40;
  mana_cost[3] = 70;
  mana_cost[4] = 110;
  mana_cost[5] = 160;
  mana_cost[6] = 210;
  mana_cost[7] = 265;
  mana_cost[8] = 315;
  mana_cost[9] = 370;
  mana_cost[10] = 380;
}
std::unordered_map<int, int> Shadowbolt::min;
std::unordered_map<int, int> Shadowbolt::max;
std::unordered_map<int, double> Shadowbolt::cast_time;
std::unordered_map<int, int> Shadowbolt::mana_cost;
Shadowbolt Shadowbolt;

// Initialize Corruption
Corruption::Corruption()
{
  tick_dmg[3] = 37;
  cast_time[3] = 2.0;
  mana_cost[3] = 100;
}
std::unordered_map<int, int> Corruption::tick_dmg;
std::unordered_map<int, double> Corruption::cast_time;
std::unordered_map<int, int> Corruption::mana_cost;
Corruption corruption;

// Initialize Life tap
LifeTap::LifeTap()
{

  conversion[2] = 75;
}

std::unordered_map<int, double> LifeTap::conversion;
LifeTap lifetap;
}  // namespace spells
