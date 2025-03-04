#pragma once
#include "env.hpp"
#include "ioc.hpp"

COMPONENT(SINGLETON, ReplayBuffer, public : void store(const Replay &data);
          std::vector<Replay> sample(int number) const;)
