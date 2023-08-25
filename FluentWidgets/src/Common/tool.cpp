#include "tool.h"

QString operator""_qs(const char *str, size_t len) {
    return QString(str);
}
