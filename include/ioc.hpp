#pragma once

#define CONCAT2(A, B) A##B
#define CONCAT2_DEFERRED(A, B) CONCAT2(A, B)
#define L_TRANSIENT(name)                                                      \
  name() { instance = _##name::create(); }                                     \
  ~name() { delete instance; }
#define L_SINGLETON(name)                                                      \
  name() { instance = &_##name::getInstance(); }
#define L(lifetime, name) CONCAT2_DEFERRED(L_, lifetime)(name)

#define COMPONENT(lifetime, name, ...)                                         \
  class _##name {                                                              \
  public:                                                                      \
    static _##name &getInstance() {                                            \
      static _##name instance;                                                 \
      return instance;                                                         \
    }                                                                          \
    __VA_ARGS__                                                                \
    static _##name *create() { return new _##name(); }                         \
                                                                               \
  private:                                                                     \
    _##name() {}                                                               \
    _##name(const _##name &) = delete;                                         \
    _##name &operator=(const _##name &) = delete;                              \
  };                                                                           \
  class name {                                                                 \
  public:                                                                      \
    L(lifetime, name)                                                          \
    _##name &operator*() { return *instance; }                                 \
    _##name *operator->() { return instance; }                                 \
                                                                               \
  private:                                                                     \
    _##name *instance;                                                         \
  };
