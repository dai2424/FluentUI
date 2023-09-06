#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QToolButton>

class QLabel;
class QHBoxLayout;

namespace FW {

/**
 * @brief 开关按钮指示器
 *
 */
class Indicator : public QToolButton {
    Q_OBJECT
    Q_PROPERTY(QColor sliderOnColor READ getSliderOnColor WRITE setSliderOnColor)
    Q_PROPERTY(QColor sliderOffColor READ getSliderOffColor WRITE setSliderOffColor)
    Q_PROPERTY(QColor sliderDisabledColor READ getSliderDisabledColor WRITE setSliderDisabledColor)
public:
    explicit Indicator(QWidget *parent = nullptr);

    void setChecked(bool checked);

    // 属性函数
    QColor getSliderOnColor();
    void setSliderOnColor(const QColor &color);

    QColor getSliderOffColor();
    void setSliderOffColor(const QColor &color);

    QColor getSliderDisabledColor();
    void setSliderDisabledColor(const QColor &color);

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

signals:
    void checkedChanged(bool);

private slots:
    // 刷新指示器位置
    void updateSliderPos();

private:
    // 指示器颜色
    QColor m_sliderOnColor;
    QColor m_sliderOffColor;
    QColor m_sliderDisabledColor;

    // 计时器 : 指示器划动动画
    QTimer *m_timer;

    // 内边距 、 指示器原角度
    qint32 m_padding;
    qint32 m_sliderRadius;

    // 指示器划动位置
    qreal m_sliderX;
    qreal m_sliderEndX;
    qreal m_sliderStep;
};

enum IndicatorPosition {
    LEFT  = 0,
    RIGHT = 1
};

class SwitchButton : public QWidget {
    Q_OBJECT
    Q_PROPERTY(qint32 spacing READ getSpacing WRITE setSpacing)
public:
    explicit SwitchButton(QWidget *parent = nullptr, IndicatorPosition indicatorPos = IndicatorPosition::LEFT);

    bool isChecked() const;
    void setChecked(bool checked);
    void toggleChecked();

    // 指示文本属性
    QString getOnText() const;
    void setOnText(const QString &text);

    QString getOffText() const;
    void setOffText(const QString &text);

    // 间隔属性
    qint32 getSpacing() const;
    void setSpacing(qint32 spacing);

signals:
    void checkedChanged(bool checked);

private slots:
    void textChange();

private:
    // 指示器与文本间隔
    int m_spacing;
    // 指示文本
    QString m_offText;
    QString m_onText;
    // 指示器
    Indicator *m_indicator;
    QLabel *m_label;
    IndicatorPosition m_indicatorPos;
    // 布局
    QHBoxLayout *m_hBox;
};

}  // namespace FW

#endif