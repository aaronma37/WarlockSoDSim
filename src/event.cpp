#include <effect_interface.h>
#include <event.h>
#include <state.h>

namespace {
thread_local int tls_event_idx = 0;
}

namespace events {
Event::Event (double _time, std::unique_ptr<effects::EffectI> _effect)
: time (_time), effect (std::move (_effect)) {
    event_idx = tls_event_idx;
    tls_event_idx++;
};

void Event::resolve (
std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& event_queue,
state::State& state) const {
    std::ostream& log = std::cout;
    state.time        = time;
    (*effect) (event_queue, state, log);
}

bool compareEvent (Event& a, Event& b) {
    if (a.time == b.time)
        return (a.event_idx > b.event_idx);
    return (a.time > b.time);
}
} // namespace events
