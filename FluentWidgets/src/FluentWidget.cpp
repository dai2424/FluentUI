#include "FluentWidget.h"
#include "Common/Config.h"

using namespace FW;

Theme FluentWidgets::theme() const {
    return m_theme;
}

void FluentWidgets::setTheme(const Theme theme) {
    this->m_theme = theme;
}

QColor FluentWidgets::themeColor() const {
    return m_themeColor;
}

void FluentWidgets::setThemeColor(const QColor &color) {
    this->m_themeColor = color;
}

bool FluentWidgets::isDark() {
    return m_theme == Theme::DARK;
}

FluentWidgets &FluentWidgets::getInstance() {
    static FluentWidgets instance;
    return instance;
}

FluentWidgets::FluentWidgets()
    : m_theme(Theme::AUTO), m_themeColor(QColor("#FFC0CB")), QObject(nullptr) {
}

FluentWidgets::~FluentWidgets() {}