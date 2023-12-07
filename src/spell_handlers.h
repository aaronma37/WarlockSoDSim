#pragma once

#include <effects.h>
#include <spell_handler_interface.h>
#include <spells.h>
#include <state.h>

namespace spells {
struct ShadowboltSpellHandler : public spells::SpellHandlerI {
    ShadowboltSpellHandler (std::string _caster_id, int _rank);
    int rank;

    void operator() (
    std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& _event_queue,
    state::State& _state,
    std::ostream& _os);
};

struct CorruptionSpellHandler : public spells::SpellHandlerI {
    CorruptionSpellHandler (std::string _caster_id, int _rank);
    int rank;

    void operator() (
    std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& _event_queue,
    state::State& _state,
    std::ostream& _os);
};
} // namespace spells
