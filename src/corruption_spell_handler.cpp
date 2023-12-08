#include <spell_handlers.h>

namespace spells {
CorruptionSpellHandler::CorruptionSpellHandler (std::string _caster_id, int _rank)
: spells::SpellHandlerI (_caster_id, spells::Corruption::cast_time[_rank]),
  rank (_rank) {
}

void CorruptionSpellHandler::operator() (
std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& _event_queue,
state::State& _state,
std::ostream& _os) {
    const auto& caster_state      = _state.casters[this->caster_id];
    utils::CastPointResult result = utils::nonBinaryCast (
    _state.casters[this->caster_id].crit_chance, _state.casters[this->caster_id].hit_chance);
    double crit_mod = 1.0;

    if (result.hit) {
        double dmg =
        utils::nonBinaryDamageCalculation (spells::Corruption::tick_dmg[rank],
        spells::Corruption::tick_dmg[rank], caster_state.spell_power,
        spells::Corruption::coefficient, crit_mod, result.partial_resist_mod, {});

        _os << _state.time << ": " << caster_id << " casted R4 Corruption\n";
        const double snapshot_tick_dmg = spells::Corruption::tick_dmg[rank];
        _state.debuffs.corruption_ids[caster_id] = _state.time;

        _event_queue.push (events::Event (_state.time + 3,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg)));
        _event_queue.push (events::Event (
        _state.time + 3, std::make_unique<effects::NightfallRoll> (caster_id)));

        _event_queue.push (events::Event (_state.time + 6,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg)));
        _event_queue.push (events::Event (
        _state.time + 6, std::make_unique<effects::NightfallRoll> (caster_id)));

        _event_queue.push (events::Event (_state.time + 9,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg)));
        _event_queue.push (events::Event (
        _state.time + 9, std::make_unique<effects::NightfallRoll> (caster_id)));

        _event_queue.push (events::Event (_state.time + 12,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg)));
        _event_queue.push (events::Event (
        _state.time + 12, std::make_unique<effects::NightfallRoll> (caster_id)));

        _event_queue.push (events::Event (_state.time + 15,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg)));
        _event_queue.push (events::Event (
        _state.time + 15, std::make_unique<effects::NightfallRoll> (caster_id)));

        _event_queue.push (events::Event (_state.time + 18,
        std::make_unique<effects::CorruptionTick> (caster_id, rank, _state.time, dmg, true)));
        _event_queue.push (events::Event (
        _state.time + 18, std::make_unique<effects::NightfallRoll> (caster_id)));
    } else {
        _os << _state.time << ": " << caster_id << " casted R4 Corruption; resisted;\n";
    }
}
} // namespace spells
