#include <combat_log.h>
#include <spell_handlers.h>

namespace spells
{
CorruptionSpellHandler::CorruptionSpellHandler(std::string _caster_id, int _rank)
  : spells::SpellHandlerI(_caster_id, spells::Corruption::cast_time[_rank]), rank(_rank)
{
}

void CorruptionSpellHandler::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  const auto& casterstate = state.casters[this->caster_id];
  utils::CastPointResult result =
      utils::nonBinaryCast(state.casters[this->caster_id].crit_chance, state.casters[this->caster_id].hit_chance);
  double crit_mod = 1.0;

  if (result.hit)
  {
    double dmg = utils::nonBinaryDamageCalculation(spells::Corruption::tick_dmg[rank],
                                                   spells::Corruption::tick_dmg[rank],
                                                   casterstate.spell_power,
                                                   spells::Corruption::coefficient,
                                                   crit_mod,
                                                   result.partial_resist_mod,
                                                   {});

    log.addLogEvent(state.time, this->caster_id, std::string(" casted R" + std::to_string(rank) + " Corruption; hit."));
    const double snapshot_tick_dmg = spells::Corruption::tick_dmg[rank];
    state.debuffs.corruption_ids[caster_id] = state.time;

    event_queue.push(
        events::Event(state.time + 3, std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg)));
    event_queue.push(events::Event(state.time + 3, std::make_unique<effects::NightfallRoll>(caster_id)));

    event_queue.push(
        events::Event(state.time + 6, std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg)));
    event_queue.push(events::Event(state.time + 6, std::make_unique<effects::NightfallRoll>(caster_id)));

    event_queue.push(
        events::Event(state.time + 9, std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg)));
    event_queue.push(events::Event(state.time + 9, std::make_unique<effects::NightfallRoll>(caster_id)));

    event_queue.push(
        events::Event(state.time + 12, std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg)));
    event_queue.push(events::Event(state.time + 12, std::make_unique<effects::NightfallRoll>(caster_id)));

    event_queue.push(
        events::Event(state.time + 15, std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg)));
    event_queue.push(events::Event(state.time + 15, std::make_unique<effects::NightfallRoll>(caster_id)));

    event_queue.push(events::Event(state.time + 18,
                                   std::make_unique<effects::CorruptionTick>(caster_id, rank, state.time, dmg, true)));
    event_queue.push(events::Event(state.time + 18, std::make_unique<effects::NightfallRoll>(caster_id)));
  }
  else
  {
    log.addLogEvent(state.time, this->caster_id, std::string(" casted R4 Corruption; resisted."));
  }
}
}  // namespace spells
