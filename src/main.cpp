#include <actions.h>
#include <combat_log.h>
#include <effect_interface.h>
#include <effects.h>
#include <event.h>
#include <fwds.h>
#include <policies.h>
#include <spell_handler_interface.h>
#include <spell_handlers.h>
#include <spells.h>
#include <state.h>
#include <utils.h>

#include <chrono>
#include <ctime>
#include <functional>
#include <memory>
#include <omp.h>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

static constexpr int k_time_sec = 200;
static constexpr int k_iters = 1;
std::array<state::State, k_iters> g_final_state_arr;

namespace
{
state::State build1(std::string caster_id)
{
  state::State state;
  state.casters[caster_id].policy_id = policies::PolicyID::CORRUPTION_OVER_SHADOWBOLT;
  return state;
}

state::State build2(std::string caster_id)
{
  state::State state;
  state.casters[caster_id].policy_id = policies::PolicyID::ONLY_SHADOWBOLTS;
  return state;
}

state::State build3(std::string caster_id)
{
  state::State state;
  state.casters[caster_id].policy_id = policies::PolicyID::ONLY_CORRUPTIONS;
  return state;
}

static std::unordered_map<std::string, std::function<state::State(std::string)>> build_map;

void makeBuilds()
{
  build_map["Build1"] = [](std::string s)
  {
    return build1(s);
  };
  build_map["Build2"] = [](std::string s)
  {
    return build2(s);
  };
  build_map["Build3"] = [](std::string s)
  {
    return build3(s);
  };
}
}  // namespace

namespace
{
using EventQueue =
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>;
void runSim(std::string build_type)
{
  const std::string caster_id = "Player";
  logging::CombatLog combat_log;
  state::State state = build_map[build_type](caster_id);

  EventQueue event_queue(events::compareEvent);
  event_queue.push(events::Event(1, std::make_unique<::effects::GCD>(caster_id)));

  while (state.time < 1000 && !event_queue.empty())
  {
    auto& event = event_queue.top();
    event.resolve(event_queue, state, combat_log);
    event_queue.pop();
  }

  combat_log.print();
  state::postProcess(state);
  // std::cout << omp_get_thread_num() << " " << state << std::endl;
  g_final_state_arr[omp_get_thread_num()] = state;
};
}  // namespace

int main(int argc, char** argv)
{
  makeBuilds();
  auto start = std::chrono::steady_clock::now();
  std::srand(1000);
#pragma omp parallel num_threads(k_iters)
  {
    runSim(argv[1]);
  }
  double avg = 0;
  for (int i = 0; i < k_iters; i++)
  {
    avg += g_final_state_arr[i].dps / k_iters;
  }
  auto end = std::chrono::steady_clock::now();
  auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  std::cout << argv[1] << ": Runtime: " << dur << "mS. " << (k_iters * k_time_sec * 1000 / dur)
            << " (simtime/cputime)."
            << " Avg dps: " << avg << ". Iterations: " << k_iters << "\n";
  return 0;
}
