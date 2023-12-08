#pragma once

#include <fwds.h>

#include <iostream>
#include <memory>
#include <queue>

namespace events {
struct Event {
    Event (double _time, std::unique_ptr<effects::EffectI> _effect);
    Event () = delete;

    void resolve (
    std::priority_queue<events::Event, std::vector<events::Event>, decltype (&events::compareEvent)>& event_queue,
    state::State& state) const;

    double time;
    std::unique_ptr<effects::EffectI> effect;
    int event_idx;
};

bool compareEvent (Event& a, Event& b);
} // namespace events
