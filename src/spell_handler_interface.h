#pragma once

#include <fwds.h>

#include <queue>
#include <string>

namespace spells
{
struct SpellHandlerI
{
  SpellHandlerI(std::string _caster_id, double _cast_time) : caster_id(_caster_id), cast_time(_cast_time)
  {
  }
  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>&,
      state::State&,
      std::ostream&) = 0;

  virtual ~SpellHandlerI(){};

  const std::string caster_id;
  double cast_time = 0;
};
}  // namespace spells
