#pragma once

#include <spell_handlers.h>
#include <spells.h>
#include <state.h>

namespace actions {
inline void cast (const std::string& caster_id,
double cast_time,
const state::State& state,
std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& event_queue,
std::ostream& os,
int rank,
std::unique_ptr<spells::SpellHandlerI> spell_handler) {
    event_queue.push (events::Event (state.time + cast_time,
    std::make_unique<::effects::Cast> (caster_id, std::move (spell_handler), cast_time)));
}

} // namespace actions
