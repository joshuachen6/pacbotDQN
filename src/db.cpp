#include "db.hpp"
#include <sqlite_orm/sqlite_orm.h>

auto storage = sqlite_orm::make_storage(
    "database.db", sqlite_orm::make_table(
                       "ReplayBuffer",
                       sqlite_orm::make_column("gameIndex", &Replay::gameIndex),
                       sqlite_orm::make_column("stepIndex", &Replay::stepIndex),
                       sqlite_orm::make_column("state", &Replay::state),
                       sqlite_orm::make_column("action", &Replay::action),
                       sqlite_orm::make_column("reward", &Replay::reward)));

void _ReplayBuffer::store(const Replay &replay) {}

std::vector<Replay> _ReplayBuffer::sample(int number) const { return {}; }
