#include <combat_log.h>
#include <policies.h>

namespace
{
using EventQueue = std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>;

void castShadowbolt(
    const std::string& caster_id, EventQueue& event_queue, state::State& state, logging::CombatLog& log, int rank)
{
  log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Shadowbolt.");
  double cast_time = spells::Shadowbolt::cast_time[rank];
  cast_time -= state.casters.at(caster_id).talents.bane * .1;
  if (state.casters.at(caster_id).nightfall)
  {
    cast_time = 0;
    state.casters[caster_id].nightfall = false;
  }
  actions::cast(caster_id,
                cast_time,
                state,
                event_queue,
                log,
                rank,
                std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank, cast_time));
}

void castCorruption(
    const std::string& caster_id, EventQueue& event_queue, state::State& state, logging::CombatLog& log, int rank)
{
  double cast_time = spells::Corruption::cast_time[rank];
  cast_time -= state.casters.at(caster_id).talents.improved_corruption * .4;
  log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Corruption.");

  actions::cast(caster_id,
                cast_time,
                state,
                event_queue,
                log,
                rank,
                std::make_unique<spells::CorruptionSpellHandler>(caster_id, rank));
}

// POLICIES
void OnlyShadowbolts(const std::string& caster_id,
                     EventQueue& event_queue,
                     state::State& state,
                     logging::CombatLog& log)
{
  static constexpr int rank = 4;
  castShadowbolt(caster_id, event_queue, state, log, rank);
}

void OnlyCorruptions(const std::string& caster_id,
                     EventQueue& event_queue,
                     state::State& state,
                     logging::CombatLog& log)
{
  static constexpr int rank = 3;
  castCorruption(caster_id, event_queue, state, log, rank);
}

void CorruptionOverShadowbolt(const std::string& caster_id,
                              EventQueue& event_queue,
                              state::State& state,
                              logging::CombatLog& log)
{
  if (state.debuffs.corruption_ids.count(caster_id) == 0 || state.debuffs.corruption_ids.at(caster_id) == 0)
  {
    static constexpr int rank = 3;
    castCorruption(caster_id, event_queue, state, log, rank);
  }
  else
  {
    static constexpr int rank = 4;
    castShadowbolt(caster_id, event_queue, state, log, rank);
  }
}

}  // namespace

namespace policies
{
void act(const std::string& caster_id, EventQueue& event_queue, state::State& state, logging::CombatLog& log)
{
  if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_SHADOWBOLTS)
    OnlyShadowbolts(caster_id, event_queue, state, log);
  else if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_CORRUPTIONS)
    OnlyCorruptions(caster_id, event_queue, state, log);
  else if (state.casters.at(caster_id).policy_id == policies::PolicyID::CORRUPTION_OVER_SHADOWBOLT)
    CorruptionOverShadowbolt(caster_id, event_queue, state, log);
}
}  // namespace policies
