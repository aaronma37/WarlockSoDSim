#include <effect_interface.h>
#include <event.h>
#include <state.h>

namespace events
{
Event::Event(double _time, std::unique_ptr<effects::EffectI> _effect) : time(_time), effect(std::move(_effect)){};

void Event::resolve(
    std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
    state::State& state) const
{
  std::ostream& log = std::cout;
  state.time = time;
  (*effect)(event_queue, state, log);
}

bool compareEvent(Event& a, Event& b)
{
  return (a.time > b.time);
}
}  // namespace events
