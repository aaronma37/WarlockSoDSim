#pragma once

#include <actions.h>
#include <event.h>
#include <state.h>

#include <string>

namespace policies
{
void act(const std::string& caster_id,
         std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
         const state::State& state,
         std::ostream& os);

// void doAction(
//     const std::string& caster_id,
//     std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
//     const state::State& state,
//     std::ostream& os)
// {
//   if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_SHADOWBOLTS)
//   {
//     static constexpr int rank = 4;
//     os << state.time << ": " << caster_id << " started casting R" << rank << " Shadowbolt.\n";
//     actions::cast(
//         caster_id, state, event_queue, os, rank, std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank));
//   }
// }
}  // namespace policies
