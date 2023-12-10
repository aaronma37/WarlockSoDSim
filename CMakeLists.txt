project(WarlockSoDSim)
cmake_minimum_required(VERSION 3.16)

add_library(
  interfaces
  ${SHARED_OR_STATIC}
  src/spell_handler_interface.cpp
  src/effect_interface.cpp
  src/policies.cpp
  src/state.cpp
  src/spells.cpp
  src/event.cpp
  src/effects.cpp
  src/utils.cpp
  src/shadowbolt_spell_handler.cpp
  src/corruption_spell_handler.cpp
  src/life_tap_spell_handler.cpp
  src/utils.cpp
  src/combat_log.cpp
  src/spell_handlers.cpp)
target_include_directories(
  interfaces PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/>)

add_executable(sod_sim src/main.cpp)
target_link_libraries(sod_sim PUBLIC interfaces)

target_compile_options(sod_sim PUBLIC -fsanitize=address -fopenmp -O3 -std=c++20)
target_link_options(sod_sim PUBLIC -fsanitize=address -fopenmp -O3 -std=c++20)

# target_compile_options(sod_sim PUBLIC -fopenmp -O3 -std=c++20 -ffast-math)
# target_link_options(sod_sim PUBLIC  -fopenmp -O3 -std=c++20 -ffast-math)
