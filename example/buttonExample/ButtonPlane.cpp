#include "ButtonPlane.h"
#include <QPushButton>

ButtonWidget::ButtonWidget(QWidget *parent)
    : QWidget(parent) {
    btn = new QPushButton(this);
    btn->setText("Button");
}
