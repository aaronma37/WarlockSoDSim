#include <spell_handlers.h>

namespace spells
{
ShadowboltSpellHandler::ShadowboltSpellHandler(std::string _caster_id, int _rank, double _cast_time)
  : spells::SpellHandlerI(_caster_id, _cast_time), rank(_rank)
{
}

void ShadowboltSpellHandler::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  const auto& caster_state = state.casters[this->caster_id];
  utils::CastPointResult result =
      utils::nonBinaryCast(state.casters[this->caster_id].crit_chance, state.casters[this->caster_id].hit_chance);

  if (result.hit)
  {
    log.addLogEvent(state.time, this->caster_id, std::string(" casted R" + std::to_string(rank) + " Shadowbolt; hit."));
    double crit_mod = 1.0;
    if (result.crit)
      crit_mod = 1.5;

    std::vector<double> debuff_mods{};

    double dmg = utils::nonBinaryDamageCalculation(spells::Shadowbolt::min[rank],
                                                   spells::Shadowbolt::max[rank],
                                                   caster_state.spell_power,
                                                   spells::Shadowbolt::coefficient,
                                                   crit_mod,
                                                   result.partial_resist_mod,
                                                   debuff_mods);
    event_queue.push(events::Event(
        state.time, std::make_unique<::effects::ProjectileHit>(this->caster_id, "Shadowbolt", dmg, result)));

    if (result.crit)
    {
      event_queue.push(events::Event(state.time + 0.01, std::make_unique<::effects::ApplyISB>(this->caster_id)));
    }
    else
    {
      if (state.debuffs.isb)
      {
        state.debuffs.isb_charges -= 1;
        log.addLogEvent(state.time,
                        "",
                        std::string("ISB charges remaining: " + std::to_string(state.debuffs.isb_charges)),
                        logging::Color::PURPLE);
        if (state.debuffs.isb_charges < 1)
        {
          std::unique_ptr<::effects::RemoveISB> effect = std::make_unique<::effects::RemoveISB>(this->caster_id);
          state.debuffs.isb_addr = effect.get();
          event_queue.push(events::Event(state.time + 0.01, std::move(effect)));
        }
      }
    }
  }
  else
  {
    log.addLogEvent(state.time, this->caster_id, std::string(" casted R4 Shadowbolt; resisted."));
  }
}

}  // namespace spells
