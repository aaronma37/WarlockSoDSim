#include <policies.h>

namespace
{
using EventQueue = std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>;

// POLICIES
void OnlyShadowbolts(const std::string& caster_id, EventQueue& event_queue, const state::State& state, std::ostream& os)
{
  static constexpr int rank = 4;
  os << state.time << ": " << caster_id << " started casting R" << rank << " Shadowbolt.\n";
  actions::cast(
      caster_id, state, event_queue, os, rank, std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank));
}

void OnlyCorruptions(const std::string& caster_id, EventQueue& event_queue, const state::State& state, std::ostream& os)
{
  static constexpr int rank = 4;
  os << state.time << ": " << caster_id << " started casting R" << rank << " Corruption.\n";
  actions::cast(
      caster_id, state, event_queue, os, rank, std::make_unique<spells::CorruptionSpellHandler>(caster_id, rank));
}

}  // namespace

namespace policies
{
void act(const std::string& caster_id, EventQueue& event_queue, const state::State& state, std::ostream& os)
{
  if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_SHADOWBOLTS)
    OnlyShadowbolts(caster_id, event_queue, state, os);
  else if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_CORRUPTIONS)
    OnlyCorruptions(caster_id, event_queue, state, os);
}
}  // namespace policies
