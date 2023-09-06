#ifndef __STYLE_SHEET
#define __STYLE_SHEET

#include "Config.h"
#include "Icon.h"
#include <QMap>
#include <QObject>
#include <QVector>

namespace FW {
/**
 * @brief 样式管理器单例，用于对主题、主题色改变动态修改组件色彩
 *
 * 样式管理流程：
 *  1、注册widget至样式管理类
 *  2、当主题色改变时，重新设置所管理widget样式
 *  3、当widget销毁时，从管理类注销widget
 */
#define SSMIns StyleSheetManager::getInstance()

class StyleSheetManager : public QObject {
    Q_OBJECT
    // 禁用拷贝和移动构造
    Q_DISABLE_COPY_MOVE(StyleSheetManager)
public:
    static StyleSheetManager &getInstance();

    // 注册widget
    void registerWidget(const QString &widgetType, QWidget *widget);
    // 注销widget
    void deRegisterWidget(const QString &widgetType, QWidget *widget);
    // 注册Icon
    void registerIcon(FluentIconBase *icon);
    // 注销Icon
    void deRegisterIcon(FluentIconBase *icon);
    // 重新设置所样式管理器管理widget样式
    void resetStyle();
    // 重新设置Icon的资源
    void resetIconTheme(Theme theme);
private:
    StyleSheetManager();

    QVector<FluentIconBase *> m_icons;
    QMultiMap<QString, QWidget *> m_widgets;
};

/**
 * @brief 用于对widget设置样式单例
 *
 * 样式应用流程：
 *  1、根据widget类型、主题来获取带有占位符的字符串
 *  2、替换占位符为真正的色彩值
 *  3、应用字符串
 */
#define FSSIns FluentStyleSheet::getInstance()

class FluentStyleSheet {
    Q_DISABLE_COPY_MOVE(FluentStyleSheet)
public:
    enum Type {
        Menu = 0,
        Button,
        SwitchButton
    };

    static FluentStyleSheet &getInstance();

    // 获取路径
    QString path();
    // 获取类型字符串
    QString typeName(Type t);
    // 从资源获取原始样式字符串
    QString getStyleSheet(const QString &filePath);
    // 替换原始样式字符串的占位符
    QString applyThemeColor(const QString &qss);
    // 获取qss
    QString getQss(const QString &type, Theme theme);

    /**
     * @brief 应用qss
     *
     * @param widget 目标组件
     * @param type : Type 组件类型 : QString 组件类型名
     * @param theme  主题
     * @param reg    是否注册到样式管理器
     */
    void apply(QWidget *widget, Type type, Theme theme = Theme::AUTO, bool reg = true);
    void apply(QWidget *widget, const QString &type, Theme theme = Theme::AUTO, bool reg = true);

private:
    FluentStyleSheet();
};

/* 主题色 */
class ThemeColor {
public:
    enum Type {  // 色彩类型
        PRIMARY = 0,
        DARK_1,
        DARK_2,
        DARK_3,
        LIGHT_1,
        LIGHT_2,
        LIGHT_3
    };

    ThemeColor(Type t);

    QString type() const;  // 返回占位符 (ThemeColorPrimary,...)
    QString name() const;  // 返回主题色颜色
    QColor color() const;  // 返回处理过后的主题色

private:
    Type m_type;
};

QColor getThemeColor();  // 获取主题色
}  // namespace FW
#endif