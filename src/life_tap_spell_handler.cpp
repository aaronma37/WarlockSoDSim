#include <spell_handlers.h>
namespace
{
using SpellMetadata = spells::LifeTap;
}

namespace spells
{
LifeTapSpellHandler::LifeTapSpellHandler(std::string _caster_id, int _rank, double _cast_time)
    : spells::SpellHandlerI(_caster_id, _cast_time), rank(_rank)
{
}

void LifeTapSpellHandler::operator()(std::priority_queue<events::Event, std::vector<events::Event>,
                                                         decltype(&events::compareEvent)>& event_queue,
                                     state::State& state, logging::CombatLog& log)
{
  log.addLogEvent(state.time,
                  this->caster_id,
                  std::string(" casted R" + std::to_string(rank) +
                              " Lifetap. Gained: " + std::to_string(SpellMetadata::conversion[rank])));
  auto& caster_state = state.casters[this->caster_id];
  caster_state.mana += SpellMetadata::conversion[rank];
}

}  // namespace spells
