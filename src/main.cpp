
#include <actions.h>
#include <effect_interface.h>
#include <effects.h>
#include <event.h>
#include <fwds.h>
#include <spell_handler_interface.h>
#include <spell_handlers.h>
#include <spells.h>
#include <state.h>
#include <utils.h>

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <omp.h>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

namespace
{
using EventQueue = std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>;
}

namespace policies
{
void doAction(const std::string& caster_id, EventQueue& event_queue, const state::State& state, std::ostream& os)
{
  if (state.casters.at(caster_id).policy_id == policies::PolicyID::ONLY_SHADOWBOLTS)
  {
    static constexpr int rank = 4;
    os << state.time << ": " << caster_id << " started casting R" << rank << " Shadowbolt.\n";
    actions::cast(
        caster_id, state, event_queue, os, rank, std::make_unique<spells::ShadowboltSpellHandler>(caster_id, rank));
  }
}
}  // namespace policies

namespace
{
void runSim()
{
  const std::string caster_id = "Player";
  state::State state;
  state.casters[caster_id].policy_id = policies::PolicyID::ONLY_SHADOWBOLTS;
  state.casters[caster_id].talents.improved_shadow_bolt = true;

  EventQueue event_queue(events::compareEvent);
  event_queue.push(events::Event(1, std::make_unique<::effects::GCD>(caster_id)));

  while (state.time < 60 && !event_queue.empty())
  {
    auto& event = event_queue.top();
    event.resolve(event_queue, state);
    event_queue.pop();
  }

  state::postProcess(state);

  std::cout << state << std::endl;
};
}  // namespace

int main()
{
  std::srand(1000);
#pragma omp parallel num_threads(1)
  {
    runSim();
  }
  return 0;
}