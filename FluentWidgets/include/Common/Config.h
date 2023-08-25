#ifndef __CONFIG_H
#define __CONFIG_H

#include <QString>

namespace FW {
enum Theme {
    LIGHT = 0,
    DARK,
    AUTO
};

static inline QString ThemeString(Theme theme) {
    switch(theme) {
        case LIGHT:
            return "Light";
        case DARK:
            return "Dark";
        case AUTO:
            return "Auto";
    }
}
}  // namespace FW

#endif