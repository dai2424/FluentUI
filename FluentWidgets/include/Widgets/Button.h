#ifndef __BUTTON_H
#define __BUTTON_H

#include "Icon.h"
#include <QObject>
#include <QPushButton>
#include <QToolButton>

namespace FW {

class PushButton : public QPushButton {
    Q_OBJECT
public:
    explicit PushButton(const QString &text, QWidget *parent = nullptr, bool reg = true);
    explicit PushButton(const QString &text, FluentIconBase *ficon, QWidget *parent = nullptr, bool reg = true);

    void setFontSize(qint32 size);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void drawIcon(QPainter *painter, const QRect &rect);
    bool m_isPressed;
    QScopedPointer<FluentIconBase> m_fIcon;
};

class PrimaryPushButton : public PushButton {
    Q_OBJECT
public:
    explicit PrimaryPushButton(const QString &text, QWidget *parent = nullptr, bool reg = true);
    explicit PrimaryPushButton(const QString &text, FluentIconBase *ficon, QWidget *parent = nullptr, bool reg = true);

    void drawIcon(QPainter *painter, const QRect &rect) override;
};

class ToolPushButton : public QToolButton {
    Q_OBJECT
public:
    explicit ToolPushButton(FluentIconBase *fIcon, QWidget *parent = nullptr, bool reg = true);

    void setIcon(FluentIconBase *fIcon);
    FluentIconBase *fIcon() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    bool m_isPressed;
    QScopedPointer<FluentIconBase> m_fIcon;
};

}  // namespace FW
#endif