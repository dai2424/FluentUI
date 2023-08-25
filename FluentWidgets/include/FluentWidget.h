#ifndef __FLUENT_WIDGETS_H
#define __FLUENT_WIDGETS_H

#include <Common\StyleSheet.h>
#include <QColor>
#include <QObject>

namespace FW {
/**
 * @brief 库style、Theme管理
 *
 */
class FluentWidgets : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FluentWidgets)
public:
    /* theme */
    Theme theme() const;
    void setTheme(const Theme theme = Theme::AUTO);

    QColor themeColor() const;
    void setThemeColor(const QColor &color);

    bool isDark();

    /* single */
    static FluentWidgets &getInstance();

private:
    FluentWidgets();
    ~FluentWidgets();

    QColor m_themeColor;  // 主题颜色
    Theme m_theme;        // 主题
};

#define FWIns FluentWidgets::getInstance()
}  // namespace FW

#endif