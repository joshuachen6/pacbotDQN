#pragma once
#include <torch/torch.h>

/**
 * @class Replay
 * @brief Record to store in the replay buffer
 *
 */
struct Replay {
  int gameIndex;
  int stepIndex;

  std::string state;
  int action;
  double reward;
};

/**
 * @class Environment
 * @brief The environment for training
 *
 */
struct Environment {
  virtual ~Environment() = default;
  /**
   * @brief Gets the observation of the space
   */
  virtual torch::Tensor &getObservation() const = 0;
  /**
   * @brief Gets the reward
   *
   * @return The reward
   */
  virtual double getReward() const = 0;
  /**
   * @brief Checks to see if the game has terminated
   *
   * @return Whether the game has terminated
   */
  virtual bool isTerminated() const = 0;
  /**
   * @brief Steps the game forwards one step
   *
   * @param action The action to take
   */
  virtual void step(int action) = 0;
  /**
   * @brief Resets the environment
   */
  virtual void reset() = 0;
};
