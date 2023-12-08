#pragma once

#include <iostream>
#include <string>
#include <vector>
namespace
{
const std::string red("\033[0;31m");
const std::string cyan("\033[0;36m");
const std::string reset("\033[0m");
}  // namespace

namespace logging
{
enum class Color
{
  WHITE,
  RED,
  PURPLE,

};
struct LogEvent
{
  LogEvent(double _time, const std::string& _owner, const std::string& _note, Color _color = Color::WHITE)
    : time(_time), owner(_owner), note(_note), color(_color)
  {
  }
  LogEvent() = delete;

  double time;
  std::string owner;
  std::string note;
  Color color;
};

struct CombatLog
{
  std::vector<LogEvent> log;

  void addLogEvent(double _time, const std::string& _owner, const std::string& _note, Color _color = Color::WHITE)
  {
    log.push_back(LogEvent(_time, _owner, _note, _color));
  }

  void print()
  {
    for (const auto& e : log)
      std::cout << e.time << ": [" << e.owner << "]" << cyan << e.note << reset << "\n";
  }
};
}  // namespace logging
