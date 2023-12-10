#pragma once

#include <combat_log.h>
#include <effects.h>
#include <spell_handler_interface.h>
#include <spells.h>
#include <state.h>

namespace spells
{
struct ShadowboltSpellHandler : public spells::SpellHandlerI
{
  ShadowboltSpellHandler(std::string _caster_id, int _rank, double _cast_time);
  int rank;

  void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>&,
      state::State&, logging::CombatLog&);
};

struct CorruptionSpellHandler : public spells::SpellHandlerI
{
  CorruptionSpellHandler(std::string _caster_id, int _rank);
  int rank;

  void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>&,
      state::State&, logging::CombatLog&);
};

struct LifeTapSpellHandler : public spells::SpellHandlerI
{
  LifeTapSpellHandler(std::string _caster_id, int _rank, double _cast_time);
  int rank;

  void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>&,
      state::State&, logging::CombatLog&);
};
}  // namespace spells
