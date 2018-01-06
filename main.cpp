#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow mainWin;

    a.setStyleSheet("QScrollBar:horizontal {\n"
                        "border: 1px solid rgb(241, 239, 239);\n"
                        "border-left:0px;\n"
                        "border-right:0px;\n"
                        "border-bottom:0px;\n      "
                        "background: #ffffff;\n      "
                        "height: 15px;\n      "
                        "margin: 0px 0px 0 0px;\n  }\n  "
                        "QScrollBar::handle:horizontal {\n      "
                        "background: rgb(180,180, 180);\n      "
                        "min-width: 20px;\n	  "
                        "margin: 3px 3px 3 3px;\n"
                        "border-radius:0px;\n  }\n  "
                        "QScrollBar::handle:horizontal:hover {\n      "
                        "background: rgb(150,150, 150);\n  }\n "
                        "QScrollBar::add-line:horizontal {\n   "
                        "width: 0px;\n  }\n\n  "
                        "QScrollBar::sub-line:horizontal {\n      "
                        "width: 0px;\n  "
                        "}\n/**/\n "
                        "QScrollBar:vertical {\n      "
                        "border: 1px solid rgb(241, 239, 239);\n"
                        "border-top:0px;\n"
                        "border-right:0px;\n"
                        "border-bottom:0px;\n     "
                        " background: #ffffff;\n      "
                        "width: 15px;\n      "
                        "margin: 0px 0px 0 0px;\n  "
                        "}\n  "
                        "QScrollBar::handle:vertical {\n      "
                        "background: rgb(180,180, 180);\n     "
                        "min-height: 20px;\n	  "
                        "margin: 3px 3px 3 3px;\n"
                        "border-radius:0px;\n  "
                        "}\n  "
                        "QScrollBar::handle:vertical:hover {\n      "
                        "background: rgb(150,150, 150);\n  "
                        "}\n "
                        "QScrollBar::add-line:vertical {\n   "
                        "width: 0px;\n  "
                        "}\n\n  "
                        "QScrollBar::sub-line:vertical {\n      "
                        "width: 0px;\n  }\n"
                        );

    return a.exec();
}
