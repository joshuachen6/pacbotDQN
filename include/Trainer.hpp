#pragma once
#include "Database.hpp"
#include "IEnvironment.hpp"
#include <torch/nn/module.h>

/**
 * @class Trainer
 * @brief Trainer for training the neural network
 *
 */
class Trainer {
private:
  int numSimulations;
  int epochs;
  int maxSteps;

  ReplayBuffer replayBuffer;

  std::vector<std::unique_ptr<IEnvironment>> envs;

public:
  /**
   * @brief Constructs a new trainer
   *
   * @param numSimulations The number of concurrent simulations to run
   */
  Trainer(int numSimulations = 1);
  /**
   * @brief Train the neural network
   *
   * @param model The model to train
   * @param epochs The number of epochs
   * @param maxSteps The maximum number of steps to run in an epoch
   */
  void train(const torch::nn::Module &model, int epochs, int maxSteps);
};
