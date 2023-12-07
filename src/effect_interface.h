#pragma once

#include <fwds.h>
#include <queue>
#include <string>

namespace effects
{
struct EffectI
{
  EffectI(std::string _caster_id) : caster_id(_caster_id)
  {
  }
  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>&,
      state::State&,
      std::ostream&) = 0;

  virtual ~EffectI(){};

  const std::string caster_id;
};
}  // namespace effects
