#include "Button.h"
#include "StyleSheet.h"
#include <FluentWidget.h>
#include <Icon.h>
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QPushButton>
#include <QRegularExpression>
#include <QSvgRenderer>
#include <QWidget>
#include <QXmlAttributes>
#include <QtSvg>
using namespace FW;

class TestWidget : public QWidget {
    Q_OBJECT
public:
    TestWidget(QWidget *parent = nullptr)
        : QWidget(nullptr) {
        this->setStyleSheet("background : rgb(52, 52, 52)");
        QLayout *layout  = new QVBoxLayout(this);
        PushButton *btn1 = new PushButton("Button", this);
        btn1->resize(200, 40);

        FluentIcon *icon2 = new FluentIcon(FluentIcon::Menu);
        PushButton *btn2  = new PushButton("AddButton", icon2, this);
        btn2->resize(200, 40);

        PrimaryPushButton *btn3 = new PrimaryPushButton("PrimaryPushBurron", this);
        btn3->resize(200, 40);

        FluentIcon *icon4       = new FluentIcon(FluentIcon::Menu);
        PrimaryPushButton *btn4 = new PrimaryPushButton("PrimaryPushBurron", icon4, this);
        btn4->resize(200, 40);

        layout->addWidget(btn1);
        layout->addWidget(btn2);
        layout->addWidget(btn3);
        layout->addWidget(btn4);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QWidget::paintEvent(event);
    }
};

int main(int argc, char **argv) {
    Q_INIT_RESOURCE(fluentwidgets);
    FWIns.setTheme(Theme::DARK);
    QApplication a(argc, argv);
    TestWidget w;
    w.show();
    return a.exec();
}

#include "main.moc"