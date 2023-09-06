#include "SwitchButton.h"
#include "FluentWidget.h"
#include "StyleSheet.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QStyle>
#include <QTimer>

#include <QDebug>
using namespace FW;

Indicator::Indicator(QWidget *parent)
    : QToolButton(parent),
      m_sliderOnColor(QColor(Qt::black)),
      m_sliderOffColor(QColor(Qt::white)),
      m_sliderDisabledColor(QColor(155, 154, 153)),
      m_timer(new QTimer(this)) {
    // 初始化按钮状态
    setCheckable(true);
    QToolButton::setChecked(false);

    // 初始化
    resize(36, 16);

    m_padding      = height() / 4;
    m_sliderX      = m_padding;
    m_sliderEndX   = width() - 2 * m_sliderRadius - m_padding;
    m_sliderRadius = (height() - 2 * m_padding) / 2;
    m_sliderStep   = width() / 50.0;
    connect(m_timer, &QTimer::timeout, this, &Indicator::updateSliderPos);
}

void Indicator::setChecked(bool checked) {
    if(checked == this->isChecked()) {
        return;
    }

    QToolButton::setChecked(checked);
    m_sliderRadius = (this->height() - 2 * m_padding) / 2;
    m_sliderEndX   = checked ? (this->width() - 2 * m_sliderRadius - m_padding) : m_padding;

    emit checkedChanged(checked);
}

QColor Indicator::getSliderOnColor() {
    return m_sliderOnColor;
}

void Indicator::setSliderOnColor(const QColor &color) {
    m_sliderOnColor = color;
}

QColor Indicator::getSliderOffColor() {
    return m_sliderOffColor;
}

void Indicator::setSliderOffColor(const QColor &color) {
    m_sliderOffColor = color;
}

QColor Indicator::getSliderDisabledColor() {
    return m_sliderDisabledColor;
}

void Indicator::setSliderDisabledColor(const QColor &color) {
    m_sliderDisabledColor = color;
}

void Indicator::mouseReleaseEvent(QMouseEvent *event) {
    QToolButton::mouseReleaseEvent(event);
    m_sliderEndX = isChecked() ? (this->width() - 2 * m_sliderRadius - m_padding) : m_padding;
    m_timer->start(5);

    emit checkedChanged(isChecked());
}

void Indicator::paintEvent(QPaintEvent *event) {
    // the background and border are specified by qss
    QToolButton::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    QColor color;
    if(isEnabled()) {
        color = isChecked() ? m_sliderOnColor : m_sliderOffColor;
    }
    else {
        color = m_sliderDisabledColor;
    }

    painter.setBrush(color);
    painter.drawEllipse(int(m_sliderX), m_padding, m_sliderRadius * 2, m_sliderRadius * 2);
}

void Indicator::resizeEvent(QResizeEvent *event) {
    m_padding      = this->height() / 4;
    m_sliderRadius = (height() - 2 * m_padding) / 2;
    m_sliderStep   = width() / 50.0;
    m_sliderEndX   = isChecked() ? (this->width() - 2 * m_sliderRadius - m_padding) : m_padding;
    update();
}

void Indicator::updateSliderPos() {
    if(isChecked()) {
        if(m_sliderX + m_sliderStep < m_sliderEndX) {
            m_sliderX += m_sliderStep;
        }
        else {
            m_sliderX = m_sliderEndX;
            m_timer->stop();
        }
    }
    else {
        if(m_sliderX - m_sliderStep > m_padding) {
            m_sliderX -= m_sliderStep;
        }
        else {
            m_sliderX = m_padding;
            m_timer->stop();
        }
    }

    // 刷新样式
    this->style()->polish(this);
}

SwitchButton::SwitchButton(QWidget *parent, IndicatorPosition indicatorPos)
    : QWidget(parent),
      m_indicatorPos(indicatorPos),
      m_spacing(12),
      m_hBox(new QHBoxLayout(this)),
      m_label(new QLabel(this)),
      m_indicator(new Indicator(this)) {
    setAttribute(Qt::WA_StyledBackground);
    m_hBox->setSpacing(12);
    m_hBox->setContentsMargins(0, 0, 0, 0);

    if(m_indicatorPos == IndicatorPosition::LEFT) {
        m_hBox->addWidget(m_indicator, 0, Qt::AlignLeft);
        m_hBox->addWidget(m_label, 0, Qt::AlignLeft);
        m_hBox->setAlignment(Qt::AlignLeft);
    }
    else {
        m_hBox->addWidget(m_label, 0, Qt::AlignRight);
        m_hBox->addWidget(m_indicator, 0, Qt::AlignRight);
        m_hBox->setAlignment(Qt::AlignRight);
    }

    FSSIns.apply(this, FluentStyleSheet::SwitchButton, Theme::DARK);

    connect(m_indicator, &Indicator::checkedChanged, this, &SwitchButton::checkedChanged);
    connect(m_indicator, &Indicator::checkedChanged, this, &SwitchButton::textChange);
}

bool SwitchButton::isChecked() const {
    return m_indicator->isChecked();
}

void SwitchButton::setChecked(bool checked) {
    this->adjustSize();
    m_indicator->setChecked(checked);
}

void SwitchButton::toggleChecked() {
    m_indicator->setChecked(!m_indicator->isChecked());
}

QString SwitchButton::getOnText() const {
    return m_onText;
}

void SwitchButton::setOnText(const QString &text) {
    m_onText = text;
    textChange();
}

QString SwitchButton::getOffText() const {
    return m_offText;
}

void SwitchButton::setOffText(const QString &text) {
    m_offText = text;
    textChange();
}

qint32 SwitchButton::getSpacing() const {
    return m_spacing;
}

void SwitchButton::setSpacing(qint32 spacing) {
    m_spacing = spacing;
    m_hBox->setSpacing(spacing);
    update();
}

void SwitchButton::textChange() {
    if(m_indicator->isChecked()) {
        m_label->setText(m_onText);
    }
    else {
        m_label->setText(m_offText);
    }
}