#include "PacmanEnvironment.hpp"
#include <dlfcn.h>
#include <string>

PacmanEnvironment::PacmanEnvironment() {
  // Load the shared library
  handle = dlopen("libgame.so", RTLD_LAZY);

  // Load the functions from the shared library
  _obs = (Obs)dlsym(handle, "Obs");
  _reset = (Reset)dlsym(handle, "Reset");
  _step = (Step)dlsym(handle, "Step");
  _update = (Update)dlsym(handle, "Update");

  // Reserve the observation tensor
  /* The board is 31 rows x 28 columns
   *
   * 0. Pellets
   * 1. Fruit
   * 2. Pacman
   * 3. Ghosts
   */
  observation = torch::zeros({4, 31, 28});

  // Reset score
  lastScore = 0;
  score = 0;
}

PacmanEnvironment::~PacmanEnvironment() {
  // Unload the shared library
  dlclose(handle);
}

const torch::Tensor &PacmanEnvironment::getObservation() {
  // Load the game state
  GameData game = _obs();

  // Load the pellet data
  for (int i = 0; i < 31; i++) {
    for (int ii = 0; ii < 28; ii++) {
      observation[0][i][ii] = ((game.pelletArr[i] >> ii) & 1) +
                              ((i == 3 or i == 23) and (ii == 1 or ii == 26));
    }
  }

  // Load the fruit data
  observation[1][game.fruitLoc >> 8][game.fruitLoc & 0xFF] = 1;

  // Load the Pacman data
  observation[2][game.pacmanLoc >> 8][game.pacmanLoc & 0xFF] = 1;

  // Load the Ghost data
  for (int i = 0; i < 4; i++) {
    observation[3][game.ghosts[i].location >> 8]
               [game.ghosts[i].location & 0xFF] = i + 1;
  }

  // Load the score
  lastScore = score;
  score = game.currScore;

  // Load termination
  terminated = game.currLives > 0;

  return observation;
}

double PacmanEnvironment::getReward() const { return score - lastScore; }

bool PacmanEnvironment::isTerminated() const { return terminated; }

void PacmanEnvironment::step(std::string action) {
  _step(action.c_str(), action.size());
}

void PacmanEnvironment::reset() {}
