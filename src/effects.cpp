#include <effects.h>

namespace effects
{
RemoveISB::RemoveISB(const std::string& caster_id) : EffectI(caster_id)
{
}

void RemoveISB::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  if (state.debuffs.isb_addr == this)
  {
    state.debuffs.isb = false;
    state.debuffs.isb_charges = 0;
    state.debuffs.isb_mod = 1.0;
    state.debuffs.isb_addr = 0;
    log.addLogEvent(state.time, caster_id, "ISB dissipated.");
  }
}

GCD::GCD(const std::string& caster_id) : EffectI(caster_id)
{
}

void GCD::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  log.addLogEvent(state.time, caster_id, " is off GCD.");
  policies::act(caster_id, event_queue, state, log);
}

Cast::Cast(const std::string& caster_id, std::unique_ptr<spells::SpellHandlerI> _spell_handler, double _cast_time)
  : EffectI(caster_id), spell_handler(std::move(_spell_handler))
{
}
void Cast::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  static constexpr double gcd = 1.5;
  event_queue.push(events::Event(state.time + std::max<double>(gcd - spell_handler->cast_time, 0),
                                 std::make_unique<::effects::GCD>(this->caster_id)));
  (*spell_handler)(event_queue, state, log);
}

ApplyISB::ApplyISB(std::string _caster_id) : EffectI(_caster_id)
{
}

void ApplyISB::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  state.debuffs.isb = true;
  state.debuffs.isb_charges = 4;
  state.debuffs.isb_mod = 1.2;
  std::unique_ptr<::effects::RemoveISB> effect = std::make_unique<::effects::RemoveISB>(caster_id);
  state.debuffs.isb_addr = effect.get();
  log.addLogEvent(state.time, caster_id, " ISB refreshed.");
  event_queue.push(events::Event(state.time + 12, std::move(effect)));
}

CorruptionTick::CorruptionTick(
    std::string _caster_id, int _rank, double time, double _snapshot_tick_dmg, bool _reset_after)
  : EffectI(_caster_id)
  , rank(_rank)
  , initial_cast_time(time)
  , snapshot_tick_dmg(_snapshot_tick_dmg)
  , reset_after(_reset_after)
{
}

void CorruptionTick::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  if (state.debuffs.corruption_ids[caster_id] == initial_cast_time)
  {
    state.damage_dealt += snapshot_tick_dmg;
    std::string note = " dealt " + std::to_string(snapshot_tick_dmg) + " with a corruption tick.";
    log.addLogEvent(state.time, this->caster_id, note);
    if (reset_after)
    {
      state.debuffs.corruption_ids[caster_id] = 0;
      log.addLogEvent(state.time, this->caster_id, "'s corruption dissipates.");
    }
  }
}

ProjectileHit::ProjectileHit(std::string _caster_id,
                             std::string _spell_name,
                             double _dmg,
                             utils::CastPointResult _cast_point_result)
  : EffectI(_caster_id), spell_name(_spell_name), dmg(_dmg), cast_point_result(_cast_point_result)
{
}

void ProjectileHit::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  std::string note = " dealt " + std::to_string(dmg);
  if (cast_point_result.crit)
    note += "*";
  note += " damage with " + spell_name;

  log.addLogEvent(state.time, this->caster_id, note);
  state.damage_dealt += dmg;
}

NightfallRoll::NightfallRoll(std::string _caster_id) : EffectI(_caster_id)
{
}

void NightfallRoll::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    logging::CombatLog& log)
{
  bool nightfall_proc = (((double)rand() / (RAND_MAX)) <= state.casters[this->caster_id].talents.nightfall_proc);
  if (nightfall_proc)
  {
    log.addLogEvent(state.time, "", " nightfall proc.");
    state.casters[this->caster_id].nightfall = true;
  }
}
}  // namespace effects
