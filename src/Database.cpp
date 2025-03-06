#include "Database.hpp"
#include <spdlog/spdlog.h>
#include <sqlite_orm/sqlite_orm.h>

auto storage = sqlite_orm::make_storage(
    "database.db",
    sqlite_orm::make_table("ReplayBuffer",
                           sqlite_orm::make_column("index", &Replay::index),
                           sqlite_orm::make_column("state", &Replay::state),
                           sqlite_orm::make_column("action", &Replay::action),
                           sqlite_orm::make_column("reward", &Replay::reward),
                           sqlite_orm::make_column("next", &Replay::next)));

ReplayBuffer::ReplayBuffer() { spdlog::debug("Started Database"); }

void ReplayBuffer::store(const Replay &replay) {
  // Get the already stored replay
  std::unique_ptr<Replay> storedReplay =
      storage.get_pointer<Replay>(replay.state);

  // If record does not already exist
  if (not storedReplay) {
    // Create the record
    return;
  }

  // If record already exists

  // Update the record
}

std::vector<Replay> ReplayBuffer::sample(int number) const { return {}; }
