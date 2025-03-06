#pragma once
#include "IEnvironment.hpp"

class ReplayBuffer {
public:
  ReplayBuffer();
  void store(const Replay &data);
  std::vector<Replay> sample(int number) const;
};
