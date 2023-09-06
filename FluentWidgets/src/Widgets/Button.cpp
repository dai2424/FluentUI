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
    : PushButton(text, parent, reg), m_reg(reg) {
}

PrimaryPushButton::PrimaryPushButton(const QString &text, FluentIconBase *ficon, QWidget *parent, bool reg)
    : PushButton(text, ficon, parent, reg), m_reg(reg) {
}

void PrimaryPushButton::drawIcon(QPainter *painter, const QRect &rect) {
    FluentIconBase *ic = m_fIcon.data();
    if(ic && this->isEnabled()) {
        // 如果没有注册，则不动态改变样式
        if(m_reg) {
            if(FWIns.isDark()) {
                ic->setTheme(Theme::DARK);
            }
            else {
                ic->setTheme(Theme::LIGHT);
            }
        }
    }
    else if(!this->isEnabled()) {
        painter->setOpacity(FWIns.isDark() ? 0.786 : 0.9);
    }

    PushButton::drawIcon(painter, rect);
}

ToolButton::ToolButton(FluentIconBase *fIcon, QWidget *parent, bool reg)
    : QToolButton(parent), m_fIcon(fIcon), m_isPressed(false) {
    FSSIns.apply(this, FluentStyleSheet::Button, FWIns.theme(), reg);
}

void ToolButton::setIcon(FluentIconBase *fIcon) {
    m_fIcon.reset(fIcon);
    this->update();
}

FluentIconBase *ToolButton::fIcon() const {
    return m_fIcon.data();
}

void ToolButton::mousePressEvent(QMouseEvent *event) {
    m_isPressed = true;
    QToolButton::mousePressEvent(event);
}

void ToolButton::mouseReleaseEvent(QMouseEvent *event) {
    m_isPressed = false;
    QToolButton::mouseReleaseEvent(event);
}

void ToolButton::paintEvent(QPaintEvent *event) {
    QToolButton::paintEvent(event);

    if(!m_fIcon) return;

    QPainter painter(this);

    if(!this->isEnabled()) {
        painter.setOpacity(0.43);
    }
    else {
        painter.setOpacity(0.63);
    }

    int w = this->iconSize().width();
    int h = this->iconSize().height();

    int x = (this->width() - w) / 2;
    int y = (this->height() - h) / 2;

    m_fIcon->render(&painter, QRect(x, y, w, h));
}

TransparentToolButton::TransparentToolButton(FluentIconBase *fIcon, QWidget *parent, bool reg)
    : QToolButton(parent), m_fIcon(fIcon), m_isPressed(false) {
    FSSIns.apply(this, FluentStyleSheet::Button, FWIns.theme(), reg);
}

void TransparentToolButton::setIcon(FluentIconBase *fIcon) {
    m_fIcon.reset(fIcon);
    this->update();
}

FluentIconBase *TransparentToolButton::fIcon() const {
    return m_fIcon.data();
}

void TransparentToolButton::mousePressEvent(QMouseEvent *event) {
    m_isPressed = true;
    QToolButton::mousePressEvent(event);
}

void TransparentToolButton::mouseReleaseEvent(QMouseEvent *event) {
    m_isPressed = false;
    QToolButton::mouseReleaseEvent(event);
}

void TransparentToolButton::paintEvent(QPaintEvent *event) {
    QToolButton::paintEvent(event);

    if(!m_fIcon) return;

    QPainter painter(this);

    int w = this->iconSize().width();
    int h = this->iconSize().height();

    int x = (this->width() - w) / 2;
    int y = (this->height() - h) / 2;

    m_fIcon->render(&painter, QRect(x, y, w, h));
}

RadioButton::RadioButton(const QString &text, QWidget *parent, bool reg)
    : QRadioButton(text, parent) {
    FSSIns.apply(this, FluentStyleSheet::Button, AUTO, reg);
}
