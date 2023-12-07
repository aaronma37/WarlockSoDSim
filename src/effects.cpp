#include <effects.h>

namespace effects
{
RemoveISB::RemoveISB(const std::string& caster_id) : EffectI(caster_id)
{
}

void RemoveISB::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    std::ostream& os)
{
  if (state.debuffs.isb_addr == this)
  {
    state.debuffs.isb = false;
    state.debuffs.isb_charges = 0;
    state.debuffs.isb_mod = 1.0;
    state.debuffs.isb_addr = 0;
    os << state.time << ": ISB dissipated.\n";
  }
}

GCD::GCD(const std::string& caster_id) : EffectI(caster_id)
{
}

void GCD::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    std::ostream& os)
{
  os << state.time << ": " << caster_id << " is off GCD.\n";
  policies::doAction(caster_id, event_queue, state, os);
}

Cast::Cast(const std::string& caster_id, std::unique_ptr<spells::SpellHandlerI> _spell_handler, double _cast_time)
  : EffectI(caster_id), spell_handler(std::move(_spell_handler))
{
}
void Cast::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    std::ostream& os)
{
  (*spell_handler)(event_queue, state, os);
  event_queue.push(events::Event(state.time + std::max<double>(gcd - spell_handler->cast_time, 0),
                                 std::make_unique<::effects::GCD>(this->caster_id)));
}

ApplyISB::ApplyISB(std::string _caster_id) : EffectI(_caster_id)
{
}

void ApplyISB::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    std::ostream& os)
{
  state.debuffs.isb = true;
  state.debuffs.isb_charges = 4;
  state.debuffs.isb_mod = 1.2;
  std::unique_ptr<::effects::RemoveISB> effect = std::make_unique<::effects::RemoveISB>(caster_id);
  state.debuffs.isb_addr = effect.get();
  os << state.time << ": ISB refreshed.\n";
  event_queue.push(events::Event(state.time + 12, std::move(effect)));
}

CorruptionTick::CorruptionTick(std::string _caster_id, int _rank, double time, double _snapshot_tick_dmg)
  : EffectI(_caster_id), rank(_rank), initial_cast_time(time), snapshot_tick_dmg(_snapshot_tick_dmg)
{
}

void CorruptionTick::operator()(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state,
    std::ostream& os)
{
  if (state.debuffs.corruption_ids[caster_id] == initial_cast_time)
  {
    state.damage_dealt += snapshot_tick_dmg;
    os << state.time << ": " << this->caster_id << " dealt " << snapshot_tick_dmg << " with a corruption tick.\n";
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
    std::ostream& os)
{
  os << state.time << ": " << this->caster_id << " dealt " << dmg;
  if (cast_point_result.crit)
    os << "*";

  os << " damage with " << spell_name << ".\n";
  state.damage_dealt += dmg;
}
}  // namespace effects
