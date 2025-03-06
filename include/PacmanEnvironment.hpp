#pragma once
#include <IEnvironment.hpp>

/**
 * @class GhostData
 * @brief The ghost data
 *
 */
struct GhostData {
  unsigned short location;
  unsigned char aux;
  unsigned char aux2;
};

/**
 * @class GameData
 * @brief The game data for Pacman
 *
 */
struct GameData {
  unsigned short currTicks;
  unsigned char updatePeriod;
  unsigned char gameMode;
  unsigned char modeSteps;
  unsigned char modeDuration;
  unsigned short levelSteps;
  unsigned short currScore;
  unsigned char currLevel;
  unsigned char currLives;
  unsigned char ghostCombo;
  GhostData ghosts[4];
  unsigned short pacmanLoc;
  unsigned short fruitLoc;
  unsigned char fruitSteps;
  unsigned char fruitDuration;
  unsigned pelletArr[31];
};

typedef GameData (*Obs)();
typedef void (*Reset)();
typedef void (*Step)(const char *msg, int size);
typedef void (*Update)();

class PacmanEnvironment : public IEnvironment {
private:
  torch::Tensor observation;

  double lastScore;
  double score;
  bool terminated;

  void *handle;

  Obs _obs;
  Reset _reset;
  Step _step;
  Update _update;

public:
  PacmanEnvironment();
  ~PacmanEnvironment();
  const torch::Tensor &getObservation() override;
  double getReward() const override;
  bool isTerminated() const override;
  void step(std::string action) override;
  void reset() override;
};
