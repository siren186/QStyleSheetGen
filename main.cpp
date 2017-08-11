#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    // 中文支持
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    QApplication a(argc, argv);

    int fontId = QFontDatabase::addApplicationFont("msyh.ttf");
    if (-1 != fontId)
    {
        QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(msyh, 10);
        QApplication::setFont(font);
    }

    MainWindow w;
    w.show();

    return a.exec();
}
