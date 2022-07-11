#pragma once
#include <chrono>

template <typename F, typename DurationType = std::chrono::milliseconds, typename... Args>
static DurationType duration(size_t probes, F&& func, Args&&... args) {
  using ClockType = std::chrono::steady_clock;

  auto start = ClockType::now();
  for (size_t i = 0; i < probes; ++i) {
    std::invoke(std::forward<F>(func), std::forward<Args>(args)...);
  }

  return std::chrono::duration_cast<TimeType>(ClockType::now() - start).count();
}