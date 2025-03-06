#include "Database.hpp"
#include <spdlog/spdlog.h>
#include <sqlite_orm/sqlite_orm.h>

auto storage = sqlite_orm::make_storage(
    "database.db",
    sqlite_orm::make_table("ReplayBuffer",
                           sqlite_orm::make_column("state", &Replay::state),
                           sqlite_orm::make_column("action", &Replay::action),
                           sqlite_orm::make_column("reward", &Replay::reward)));

ReplayBuffer::ReplayBuffer() { spdlog::debug("Started Database"); }

void ReplayBuffer::store(const Replay &replay) {}

std::vector<Replay> ReplayBuffer::sample(int number) const { return {}; }
