#include "Button.h"
#include "FluentWidget.h"
#include "StyleSheet.h"
#include <QDebug>
#include <QPainter>
#include <QVariant>

using namespace FW;

PushButton::PushButton(const QString &text, QWidget *parent, bool reg)
    : PushButton(text, nullptr, parent, reg) {
}

PushButton::PushButton(const QString &text, FluentIconBase *ficon, QWidget *parent, bool reg)
    : QPushButton(parent), m_isPressed(false), m_fIcon(ficon) {
    if(m_fIcon.isNull()) {
        this->setProperty("hasIcon", false);
    }
    else {
        if(m_fIcon->icon().isNull()) {
            this->setProperty("hasIcon", false);
        }
        else {
            this->setProperty("hasIcon", true);
        }
    }

    // 应用样式
    this->setText(text);
    FSSIns.apply(this, FluentStyleSheet::Button, FWIns.theme(), reg);
}

void PushButton::setFontSize(qint32 size) {
    QString fontStyle = QString("FW--PushButton { font-size: %1px; }").arg(size);
    this->setStyleSheet(this->styleSheet() + fontStyle);
}

void PushButton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);

    if(!m_fIcon) return;

    QPainter painter(this);
    if(!isEnabled()) {
        painter.setOpacity(0.43);
    }
    else if(m_isPressed) {
        painter.setOpacity(0.6);
    }

    int w  = iconSize().width();
    int h  = iconSize().height();
    int y  = (height() - h) / 2;
    int mw = this->minimumSizeHint().width();
    if(mw > 0) {
        drawIcon(&painter, QRect(12 + (width() - mw) / 2, y, w, h));
    }
    else {
        drawIcon(&painter, QRect(12, y, w, h));
    }
}

void PushButton::mousePressEvent(QMouseEvent *event) {
    m_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent *event) {
    m_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void FW::PushButton::drawIcon(QPainter *painter, const QRect &rect) {
    if(m_fIcon) {
        m_fIcon->render(painter, rect);
    }
}

PrimaryPushButton::PrimaryPushButton(const QString &text, QWidget *parent, bool reg)
    : PushButton(text, parent, reg) {
}

PrimaryPushButton::PrimaryPushButton(const QString &text, FluentIconBase *ficon, QWidget *parent, bool reg)
    : PushButton(text, ficon, parent, reg) {
}

void PrimaryPushButton::drawIcon(QPainter *painter, const QRect &rect) {
    FluentIconBase *ic = m_fIcon.data();
    if(ic && this->isEnabled()) {
        if(FWIns.isDark()) {
            ic->setTheme(Theme::LIGHT);
        }
        else {
            ic->setTheme(Theme::LIGHT);
        }
    }
    else if(!this->isEnabled()) {
        painter->setOpacity(FWIns.isDark() ? 0.786 : 0.9);
    }

    PushButton::drawIcon(painter, rect);
}

ToolPushButton::ToolPushButton(FluentIconBase *fIcon, QWidget *parent, bool reg)
    : QToolButton(parent), m_fIcon(fIcon) {
    FSSIns.apply(this, FluentStyleSheet::Button, FWIns.theme(), reg);
}
