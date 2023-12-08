#pragma once

#include <combat_log.h>
#include <fwds.h>

#include <memory>
#include <queue>

namespace events
{
struct Event
{
  Event(double _time, std::unique_ptr<effects::EffectI> _effect);
  Event() = delete;

  void resolve(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) const;

  double time;
  std::unique_ptr<effects::EffectI> effect;
  int event_idx;
};

bool compareEvent(Event& a, Event& b);
}  // namespace events
