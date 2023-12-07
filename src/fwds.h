#pragma once

#include <queue>
#include <string>
#include <vector>

namespace events
{
struct Event;
bool compareEvent(Event& a, Event& b);
}  // namespace events

namespace state
{
struct State;
}

namespace effects
{
struct EffectI;
}

namespace policies
{
void doAction(
    const std::string& caster_id,
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    const state::State& state,
    std::ostream& os);
}