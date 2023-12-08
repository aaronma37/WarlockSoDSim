#include <combat_log.h>
#include <policies.h>

namespace
{
using EventQueue = std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>;

// POLICIES
void OnlyShadowbolts(const std::string& caster_id,
                     EventQueue& event_queue,
                     const state::State& state,
                     logging::CombatLog& log)
{
  static constexpr int rank = 4;
  log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Shadowbolt.");
  double cast_time = spells::Shadowbolt::cast_time[rank];
  if (state.casters.at(caster_id).nightfall)
    cast_time = 0;
  actions::cast(caster_id,
                cast_time,
                state,
                event_queue,
                log,
                rank,
                std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank, cast_time));
}

void OnlyCorruptions(const std::string& caster_id,
                     EventQueue& event_queue,
                     const state::State& state,
                     logging::CombatLog& log)
{
  static constexpr int rank = 3;
  log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Corruption.");
  actions::cast(caster_id,
                spells::Corruption::cast_time[rank],
                state,
                event_queue,
                log,
                rank,
                std::make_unique<spells::CorruptionSpellHandler>(caster_id, rank));
}

void CorruptionOverShadowbolt(const std::string& caster_id,
                              EventQueue& event_queue,
                              const state::State& state,
                              logging::CombatLog& log)
{
  if (state.debuffs.corruption_ids.count(caster_id) == 0 || state.debuffs.corruption_ids.at(caster_id) == 0)
  {
    static constexpr int rank = 3;
    log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Corruption.");
    actions::cast(caster_id,
                  spells::Corruption::cast_time[rank],
                  state,
                  event_queue,
                  log,
                  rank,
                  std::make_unique<spells::CorruptionSpellHandler>(caster_id, rank));
  }
  else
  {
    static constexpr int rank = 4;
    log.addLogEvent(state.time, caster_id, " started casting R" + std::to_string(rank) + " Shadowbolt.");
    double cast_time = spells::Shadowbolt::cast_time[rank];
    if (state.casters.at(caster_id).nightfall)
    {
      cast_time = 0;
    }
    actions::cast(caster_id,
                  cast_time,
                  state,
                  event_queue,
                  log,
                  rank,
                  std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank, cast_time));
  }
}

}  // namespace

namespace policies
{
void act(const std::string& caster_id, EventQueue& event_queue, const state::State& state, logging::CombatLog& log)
{
  if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_SHADOWBOLTS)
    OnlyShadowbolts(caster_id, event_queue, state, log);
  else if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_CORRUPTIONS)
    OnlyCorruptions(caster_id, event_queue, state, log);
  else if (state.casters.at(caster_id).policy_id == policies::PolicyID::CORRUPTION_OVER_SHADOWBOLT)
    CorruptionOverShadowbolt(caster_id, event_queue, state, log);
}
}  // namespace policies
