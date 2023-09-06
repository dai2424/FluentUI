#include "Button.h"
#include "StyleSheet.h"
#include "SwitchButton.h"
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
        this->setStyleSheet("background : rgb(31, 31, 31)");

        QVBoxLayout *layout  = new QVBoxLayout(this);
        FluentIcon *toolIcon = new FluentIcon(FluentIcon::Setting);
        ToolButton *toolBtn  = new ToolButton(toolIcon, this);

        SwitchButton *swhBtn = new SwitchButton(this);
        swhBtn->setOnText("on");
        swhBtn->setOffText("off");

       
        layout->addWidget(toolBtn, 0, Qt::AlignCenter);
        layout->addWidget(swhBtn, 0, Qt::AlignCenter);
   

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