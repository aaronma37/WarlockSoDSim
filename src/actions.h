#pragma once

#include <spell_handlers.h>
#include <spells.h>
#include <state.h>

namespace actions
{
void cast(const std::string& caster_id,
          const state::State& state,
          std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
          std::ostream& os,
          int rank,
          std::unique_ptr<spells::SpellHandlerI> spell_handler)
{
  auto cast_time = spells::Shadowbolt::cast_time[rank];
  event_queue.push(events::Event(state.time + cast_time,
                                 std::make_unique<::effects::Cast>(caster_id, std::move(spell_handler), cast_time)));
}

// void castCorruption(
//     const std::string& caster_id, const state::State& state, EventQueue& event_queue, std::ostream& os, int rank)
// {
//   auto cast_time = spells::Corruption::cast_time[rank];
//   event_queue.push(events::Event(
//       state.time + cast_time,
//       std::make_unique<::effects::Cast>(
//           caster_id,
//           [caster_id = caster_id, rank = rank, cast_time = cast_time](
//               EventQueue& _event_queue, state::State& _state, std::ostream& _os) {
//             auto hit = (((double)rand() / (RAND_MAX)) <= _state.casters[caster_id].hit_chance);
//             const double t = _state.time;
//             if (hit)
//             {
//               _os << _state.time << ": " << caster_id << " casted R4 Corruption\n";
//               const double snapshot_tick_dmg = spells::Corruption::tick_dmg[rank];
//               _state.debuffs.corruption_ids[caster_id] = t;
//               _event_queue.push(events::Event(
//                   t + 3, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//               _event_queue.push(events::Event(
//                   t + 6, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//               _event_queue.push(events::Event(
//                   t + 9, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//               _event_queue.push(events::Event(
//                   t + 12, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//               _event_queue.push(events::Event(
//                   t + 15, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//               _event_queue.push(events::Event(
//                   t + 18, std::make_unique<effects::CorruptionTick>(caster_id, rank, t, snapshot_tick_dmg)));
//             }
//             _event_queue.push(
//                 events::Event(t + std::max<double>(gcd - cast_time, 0),
//                 std::make_unique<::effects::GCD>(caster_id)));
//           })));
// }
}  // namespace actions
