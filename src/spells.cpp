
#include <spells.h>

namespace spells
{
// Initialize Shadowbolt
Shadowbolt::Shadowbolt()
{
  min[4] = 92;
  max[4] = 104;
  cast_time[4] = 3.0;
}
std::unordered_map<int, int> Shadowbolt::min;
std::unordered_map<int, int> Shadowbolt::max;
std::unordered_map<int, double> Shadowbolt::cast_time;
Shadowbolt Shadowbolt;

// Initialize Corruption
Corruption::Corruption()
{
  tick_dmg[3] = 37;
  cast_time[3] = 2.0;
}
std::unordered_map<int, int> Corruption::tick_dmg;
std::unordered_map<int, double> Corruption::cast_time;
Corruption corruption;
}  // namespace spells
