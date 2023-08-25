#ifndef __BUTTON_WIDGET_H
#define __BUTTON_WIDGET_H

#include <QWidget>

class QPushButton;

class ButtonWidget : public QWidget {
public:
    ButtonWidget(QWidget *parent = nullptr);

private:
    QPushButton *btn;
};

#endif