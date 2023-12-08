#pragma once

#include <actions.h>
#include <event.h>
#include <state.h>

#include <string>

namespace policies {
void act (const std::string& caster_id,
std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& event_queue,
const state::State& state,
std::ostream& os);

} // namespace policies
