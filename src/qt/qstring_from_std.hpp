#pragma once

#include "game.hpp"

#include <QString>
#include <string>
#include <string_view>

// NOLINTBEGIN(*-naming)
// macros-like functions
inline QString Q_STR(std::string x) { return QString::fromStdString(x); }

inline QString Q_SVW(std::string_view x) {
  return QString::fromStdString(std::string(x));
}

#define Q_TR_GET(DATA_NAMESPACE, VAR) Q_SVW(TR_GET(DATA_NAMESPACE, VAR))

inline QString
Q_DEC(money_t val, Dec::Format format = Dec::shortF, int precision = 2) {
  return Q_STR(Dec::decimal(val, format, precision));
}
// NOLINTEND(*-naming)