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
   * 1. Power Pellets
   * 2. Fruit
   * 3. Pacman
   * 4. Ghost 1
   * 5. Ghost 2
   * 6. Ghost 3
   * 7. Ghost 4
   */
  observation = torch::zeros({8, 31, 28});

  reset();
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
      observation[1][i][ii] =
          (observation[0][i][ii] = ((game.pelletArr[i] >> ii) & 1)) &
          ((i == 3 or i == 23) and (ii == 1 or ii == 26));
    }
  }

  // Load the fruit data
  observation[2][game.fruitLoc >> 8][game.fruitLoc & 0xFF] = 1;

  // Load the Pacman data
  observation[3][game.pacmanLoc >> 8][game.pacmanLoc & 0xFF] = 1;

  // Load the Ghost data
  for (int i = 0; i < 4; i++) {
    // Set it to if the ghost 1 +  if it is vulnerable
    observation[4 + i][game.ghosts[i].location >> 8]
               [game.ghosts[i].location & 0xFF] =
                   1 + ((game.ghosts[i].aux & 0x3F0) > 0);
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
  _update();
}

void PacmanEnvironment::reset() {
  _reset();

  // Reset observation
  observation.zero_();

  // Reset score
  lastScore = 0;
  score = 0;
}
