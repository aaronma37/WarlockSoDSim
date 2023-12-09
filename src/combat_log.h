#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace logging
{
enum class Color
{
  WHITE,
  RED,
  PURPLE,
  CYAN,
  GREEN,
  GRAY,
};

inline std::string colorMap(Color color)
{
  const std::string red("\033[0;31m");
  const std::string purple("\033[0;35m");
  const std::string cyan("\033[0;36m");
  const std::string green("\033[0;32m");
  const std::string gray("\e[38;5;250m");
  const std::string reset("\033[0m");
  if (color == Color::WHITE)
    return reset;
  else if (color == Color::RED)
    return red;
  else if (color == Color::CYAN)
    return cyan;
  else if (color == Color::PURPLE)
    return purple;
  else if (color == Color::GREEN)
    return green;
  else if (color == Color::GRAY)
    return gray;
  return reset;
}

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
      std::cout << std::fixed << std::setprecision(1) << std::setw(5) << std::right << e.time << ": "
                << colorMap(e.color) << e.owner << e.note << colorMap(Color::WHITE) << "\n";
  }
};
}  // namespace logging
