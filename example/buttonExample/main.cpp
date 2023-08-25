#include "ButtonPlane.h"
#include "FluentWidget.h"
#include <Common/StyleSheet.h>
#include <QApplication>
#include <QDebug>
#include <QWidget>
#include <testButton.h>

#include <QRegExp>
#include <QRegExpValidator>

int main(int argc, char **argv) {
    QRegExp rep("aaa");
    QRegExpValidator vaildator;
    vaildator.setRegExp(rep);
}