#include "StyleSheet.h"
#include "FluentWidget.h"
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QString>
#include <QTextStream>
#include <QWidget>

using namespace FW;

StyleSheetManager::StyleSheetManager() {
}

StyleSheetManager &StyleSheetManager::getInstance() {
    static StyleSheetManager instance;
    return instance;
}

void StyleSheetManager::registerWidget(const QString &widgetType, QWidget *widget) {
    if(!m_widgets.contains(widgetType, widget)) {
        m_widgets.insert(widgetType, widget);
    }
}

void StyleSheetManager::deRegisterWidget(const QString &widgetType, QWidget *widget) {
    if(m_widgets.contains(widgetType, widget)) {
        m_widgets.remove(widgetType, widget);
    }
}

void StyleSheetManager::resetStyle() {
    // 1、获取类型列表
    for(auto type : m_widgets.keys()) {
        // 2、获取该类型下的qss
        QString qss = FSSIns.getQss(type, FWIns.theme());
        // 3、为该类型组件设置qss
        for(auto *widget : m_widgets.values(type)) {
            widget->setStyleSheet(qss);
        }
    }
}

/* FluentStyleSheet */

FluentStyleSheet::FluentStyleSheet() {
}

FluentStyleSheet &FluentStyleSheet::getInstance() {
    static FluentStyleSheet instance;
    return instance;
}

QString FluentStyleSheet::typeName(Type t) {
    switch(t) {
        case Menu:
            return "menu";
        case Button:
            return "button";
        default:
            break;
    }
    return QString();
}

QString FluentStyleSheet::path() {
    return ":/fluentwidgets/qss/";
}

QString FluentStyleSheet::getStyleSheet(const QString &filePath) {
    QFile file(filePath);
    QString rawQss = "";

    if(file.open(QIODevice::ReadOnly)) {
        // 用QTextStream读取样式文件不用区分文件编码 带bom也行
        QTextStream in(&file);
        in.setCodec("utf-8");
        while(!in.atEnd()) {
            QString line = in.readLine();
            rawQss += line + "\r\n";
        }
        file.close();
    }
    return rawQss;
}

QString FluentStyleSheet::applyThemeColor(const QString &qss) {
    static const QList<ThemeColor> colorList = {ThemeColor(ThemeColor::PRIMARY),
                                                ThemeColor(ThemeColor::DARK_1),
                                                ThemeColor(ThemeColor::DARK_2),
                                                ThemeColor(ThemeColor::DARK_3),
                                                ThemeColor(ThemeColor::LIGHT_1),
                                                ThemeColor(ThemeColor::LIGHT_2),
                                                ThemeColor(ThemeColor::LIGHT_3)};

    // 正则表达式匹配匹配
    QRegularExpression regex("--(\\w+)");
    QRegularExpressionMatchIterator matchIterator = regex.globalMatch(qss);

    QString newQss = qss;
    int offset     = 0;
    while(matchIterator.hasNext()) {
        QRegularExpressionMatch match = matchIterator.next();
        QString matchedWord           = match.captured(1);  // 获取捕获组中的单词部分

        for(const auto &color : colorList)
            if(color.type() == matchedWord) {
                int start  = match.capturedStart() - offset;
                int length = match.capturedLength();
                newQss.replace(start, length, color.name());
                offset += length - color.name().length();
            }
    }

    return newQss;
}

QString FluentStyleSheet::getQss(const QString &type, Theme theme) {
    QString themePath;
    if(theme == Theme::DARK) {
        themePath = "dark/";
    }
    else if(theme == Theme::LIGHT) {
        themePath = "light/";
    }

    // :fluentwidgets/light/button.qss
    QString filePath = path() + themePath + type + ".qss";

    QString rawQss = getStyleSheet(filePath);
    QString qss    = applyThemeColor(rawQss);
    return qss;
}

void FluentStyleSheet::apply(QWidget *widget, Type type, Theme theme, bool reg) {
    apply(widget, typeName(type), theme, reg);
}

void FluentStyleSheet::apply(QWidget *widget, const QString &type, Theme theme, bool reg) {
    if(reg) {
        SSMIns.registerWidget(type, widget);
    }
    widget->setStyleSheet(getQss(type, theme));
}

/* Theme Color*/
ThemeColor::ThemeColor(Type t)
    : m_type(t) {
}

QString ThemeColor::type() const {
    switch(m_type) {
        case PRIMARY:
            return "ThemeColorPrimary";
        case DARK_1:
            return "ThemeColorDark1";
        case DARK_2:
            return "ThemeColorDark2";
        case DARK_3:
            return "ThemeColorDark3";
        case LIGHT_1:
            return "ThemeColorLight1";
        case LIGHT_2:
            return "ThemeColorLight2";
        case LIGHT_3:
            return "ThemeColorLisght3";
        default:
            return "";
    }
}

QString ThemeColor::name() const {
    return color().name();
}

QColor ThemeColor::color() const {
    // 获取主题色
    QColor themeColor = FWIns.themeColor();

    // 转化为hsv色彩空间
    qreal h, s, v;
    themeColor.getHsvF(&h, &s, &v);

    if(FWIns.isDark()) {
        s *= 0.84;
        v = 1;
        if(m_type == DARK_1) {
            v *= 0.9;
        }
        else if(m_type == DARK_2) {
            s *= 0.977;
            v *= 0.82;
        }
        else if(m_type == DARK_3) {
            s *= 0.95;
            v *= 0.7;
        }
        else if(m_type == LIGHT_1) {
            s *= 0.92;
        }
        else if(m_type == LIGHT_2) {
            s *= 0.78;
        }
        else if(m_type == LIGHT_3) {
            s *= 0.65;
        }
    }
    else {
        if(m_type == DARK_1) {
            v *= 0.75;
        }
        else if(m_type == DARK_2) {
            s *= 1.05;
            v *= 0.5;
        }
        else if(m_type == DARK_3) {
            s *= 1.1;
            v *= 0.4;
        }
        else if(m_type == LIGHT_1) {
            v *= 1.05;
        }
        else if(m_type == LIGHT_2) {
            s *= 0.75;
            v *= 1.05;
        }
        else if(m_type == LIGHT_3) {
            s *= 0.65;
            v *= 1.05;
        }
    }

    return QColor::fromHsvF(h, qMin(s, 1.0), qMin(v, 1.0));
}

QColor getThemeColor() {
    return ThemeColor(ThemeColor::PRIMARY).color();
}
