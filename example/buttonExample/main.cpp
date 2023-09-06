#include "Button.h"
#include "StyleSheet.h"
#include <FluentWidget.h>
#include <Icon.h>
#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QPushButton>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QWidget>

using namespace FW;

class TestWidget : public QWidget {
    Q_OBJECT
public:
    TestWidget(QWidget *parent = nullptr)
        : QWidget(nullptr) {
        this->setStyleSheet("background : rgb(31, 31, 31)");

        QVBoxLayout *layout  = new QVBoxLayout(this);
        FluentIcon *toolIcon = new FluentIcon(FluentIcon::Setting);
        ToolButton *toolBtn  = new ToolButton(toolIcon, this);

        FluentIcon *toolIcon1               = new FluentIcon(FluentIcon::Setting);
        TransparentToolButton *trToolButton = new TransparentToolButton(toolIcon1, this);

        PushButton *btn1 = new PushButton("Button", this);
        btn1->resize(200, 40);

        FluentIcon *icon2 = new FluentIcon(FluentIcon::Menu);
        PushButton *btn2  = new PushButton("AddButton", icon2, this);
        btn2->resize(200, 40);

        PrimaryPushButton *btn3 = new PrimaryPushButton("PrimaryPushBurron", this);
        btn3->resize(200, 40);

        FluentIcon *icon4       = new FluentIcon(FluentIcon::Menu, DARK, true);
        PrimaryPushButton *btn4 = new PrimaryPushButton("PrimaryPushBurron", icon4, this, true);
        btn4->resize(200, 40);

        RadioButton *radio1 = new RadioButton("Radio1", this, true);
        RadioButton *radio2 = new RadioButton("Radio2", this, true);
        RadioButton *radio3 = new RadioButton("Radio3", this, true);

        layout->addWidget(toolBtn, 0, Qt::AlignCenter);
        layout->addWidget(trToolButton, 0, Qt::AlignCenter);
        layout->addWidget(btn1, 0, Qt::AlignCenter);
        layout->addWidget(btn2, 0, Qt::AlignCenter);
        layout->addWidget(btn3, 0, Qt::AlignCenter);
        layout->addWidget(btn4, 0, Qt::AlignCenter);
        layout->addWidget(radio1, 0, Qt::AlignCenter);
        layout->addWidget(radio2, 0, Qt::AlignCenter);
        layout->addWidget(radio3, 0, Qt::AlignCenter);

        this->resize(400, 500);
        connect(toolBtn, &QToolButton::clicked, this, [this]() {
            if(FWIns.isDark()) {
                FWIns.setTheme(Theme::LIGHT);
                this->setStyleSheet("background : rgb(255, 255, 255)");
            }
            else {
                FWIns.setTheme(Theme::DARK);
                this->setStyleSheet("background : rgb(31, 31, 31)");
            }
        });
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