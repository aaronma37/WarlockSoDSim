#pragma once
#include <unordered_map>

namespace spells {
struct Shadowbolt {
    Shadowbolt ();
    static constexpr double coefficient = 3 / 3.5;
    static std::unordered_map<int, int> min;
    static std::unordered_map<int, int> max;
    static std::unordered_map<int, double> cast_time;
};

struct Corruption {
    Corruption ();
    static constexpr double coefficient = 1.0;
    static std::unordered_map<int, int> tick_dmg;
    static std::unordered_map<int, double> cast_time;
};
} // namespace spells
