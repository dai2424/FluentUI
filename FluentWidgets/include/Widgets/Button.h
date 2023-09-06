#ifndef __BUTTON_H
#define __BUTTON_H

#include "Icon.h"
#include <QObject>
#include <QPushButton>
#include <QRadioButton>
#include <QToolButton>
/**
 * @brief 按钮组件库
 *
 * 1、PushButton            普通按钮
 * 2、PrimaryButton         主题色按钮
 * 3、ToolButton            工具按钮（只显示图标和边框）
 * 4、TransparentToolButton 工具按钮（只显示图标）
 */
namespace FW {

class PushButton : public QPushButton {
    Q_OBJECT
public:
    explicit PushButton(const QString &text, QWidget *parent = nullptr, bool reg = true);
    explicit PushButton(const QString &text, FluentIconBase *ficon,
                        QWidget *parent = nullptr, bool reg = true);

    /**
     * @brief 用于设置字体大小，使用Icon时需调整padding大小
     *
     * @param size
     */
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
    explicit PrimaryPushButton(const QString &text, FluentIconBase *ficon,
                               QWidget *parent = nullptr, bool reg = true);

    void drawIcon(QPainter *painter, const QRect &rect) override;

private:
    bool m_reg;
};

class ToolButton : public QToolButton {
    Q_OBJECT
public:
    explicit ToolButton(FluentIconBase *fIcon, QWidget *parent = nullptr, bool reg = true);

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

class TransparentToolButton : public QToolButton {
    Q_OBJECT
public:
    explicit TransparentToolButton(FluentIconBase *fIcon, QWidget *parent = nullptr, bool reg = true);

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

class RadioButton : public QRadioButton {
    Q_OBJECT
public:
    explicit RadioButton(const QString &text, QWidget *parent = nullptr, bool reg = true);
};

}  // namespace FW
#endif