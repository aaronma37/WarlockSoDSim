#pragma once

#include <combat_log.h>
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
      logging::CombatLog& log) override;
};

struct GCD : public EffectI
{
  GCD(const std::string& caster_id);
  GCD() = delete;

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) override;
};

struct Cast : public EffectI
{
  Cast(const std::string& caster_id, std::unique_ptr<spells::SpellHandlerI> _spell_handler, double _cast_time);
  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) override;

  std::unique_ptr<spells::SpellHandlerI> spell_handler;
};

struct ApplyISB : public EffectI
{
  ApplyISB(std::string _caster_id);

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) override;
};

struct NightfallRoll : public EffectI
{
  NightfallRoll(std::string _caster_id);

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) override;
};

struct PeriodicDamageTick : public EffectI
{
  PeriodicDamageTick(std::string _caster_id,
                     std::string _spell_name,
                     int _rank,
                     double time,
                     double _snapshot_tick_dmg,
                     bool _reset_after = false);

  std::string spell_name;
  int rank;
  double initial_cast_time;
  double snapshot_tick_dmg;
  bool reset_after;

  virtual void operator()(
      std::priority_queue<events::Event, std::vector<events::Event>, decltype(&events::compareEvent)>& event_queue,
      state::State& state,
      logging::CombatLog& log) override;
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
      logging::CombatLog& log) override;

  double dmg;
  std::string spell_name;
  utils::CastPointResult cast_point_result;
};

}  // namespace effects
