#pragma once

#include <effect_interface.h>
#include <event.h>
#include <fwds.h>
#include <memory>
#include <spell_handler_interface.h>
#include <spells.h>
#include <state.h>
#include <utils.h>

static constexpr double gcd = 1.5;

namespace effects
{
struct RemoveISB : public EffectI
{
  RemoveISB(const std::string& caster_id);

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;
};

struct GCD : public EffectI
{
  GCD(const std::string& caster_id);
  GCD() = delete;

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;
};

struct Cast : public EffectI
{
  Cast(const std::string& caster_id, std::unique_ptr<spells::SpellHandlerI> _spell_handler, double _cast_time);
  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;

  std::unique_ptr<spells::SpellHandlerI> spell_handler;
};

struct ApplyISB : public EffectI
{
  ApplyISB(std::string _caster_id);

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;
};

struct CorruptionTick : public EffectI
{
  CorruptionTick(std::string _caster_id, int _rank, double time, double _snapshot_tick_dmg);

  int rank;
  double initial_cast_time;
  double snapshot_tick_dmg;

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;
};

struct ProjectileHit : public EffectI
{
  ProjectileHit(std::string _caster_id,
                std::string _spell_name,
                double _dmg,
                utils::CastPointResult _cast_point_result);

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      std::ostream& os) override;

  double dmg;
  std::string spell_name;
  utils::CastPointResult cast_point_result;
};

}  // namespace effects